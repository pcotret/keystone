/**
 * @file enclave.h
 * @brief Enclave management interface and metadata structures for the Keystone security monitor.
 */
//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
#ifndef _ENCLAVE_H_
#define _ENCLAVE_H_

#ifndef TARGET_PLATFORM_HEADER
#error "SM requires a defined platform to build"
#endif

#include "sm.h"
#include "pmp.h"
#include "thread.h"
#include <crypto.h>

// Special target platform header, set by configure script
#include TARGET_PLATFORM_HEADER

/** @brief Maximum length of attestation data (in bytes). */
#define ATTEST_DATA_MAXLEN  1024
/* TODO: does not support multithreaded enclave yet */
/** @brief Maximum number of threads supported per enclave (currently one). */
#define MAX_ENCL_THREADS 1

/**
 * @enum enclave_state
 * @brief Represents the lifecycle state of an enclave.
 */
typedef enum {
  INVALID = -1,   ///< Uninitialized or invalid state.
  DESTROYING = 0, ///< Enclave is being destroyed.
  ALLOCATED,      ///< Resources have been allocated.
  FRESH,          ///< Enclave has been freshly initialized.
  STOPPED,        ///< Enclave has been stopped.
  RUNNING,        ///< Enclave is currently executing.
} enclave_state;

/* For now, eid's are a simple unsigned int */
/**
 * @typedef enclave_id
 * @brief Alias for enclave identifiers.
 *
 * Enclave IDs are currently implemented as simple unsigned integers.
 */
typedef unsigned int enclave_id;

/* Metadata around memory regions associate with this enclave
 * EPM is the 'home' for the enclave, contains runtime code/etc
 * UTM is the untrusted shared pages
 * OTHER is managed by some other component (e.g. platform_)
 * INVALID is an unused index
 */
/**
 * @brief Region types associated with an enclave.
 */
enum enclave_region_type{
  REGION_INVALID, ///< Unused or uninitialized region.
  REGION_EPM,     ///< Enclave Page Manager - trusted runtime memory.
  REGION_UTM,     ///< Untrusted shared memory.
  REGION_OTHER,   ///< Platform-specific or external memory region.
};

/**
 * @brief Metadata about a memory region assigned to an enclave.
 */
struct enclave_region
{
  region_id pmp_rid;             ///< PMP region identifier.
  enum enclave_region_type type; ///< Type of the region.
};

/* enclave metadata */
/**
 * @brief Metadata structure for an enclave.
 */
struct enclave
{
  //spinlock_t lock; //local enclave lock. we don't need this until we have multithreaded enclave
  enclave_id eid;          ///< Enclave identifier.
  unsigned long encl_satp; ///< Page table base for enclave virtual memory.
  enclave_state state;     ///< Current global state of the enclave.

  /* Physical memory regions associate with this enclave */
  struct enclave_region regions[ENCLAVE_REGIONS_MAX]; ///< Memory regions assigned.

  /* measurement */
  byte hash[MDSIZE];                                  ///< SHA3-512 hash measurement.
  byte sign[SIGNATURE_SIZE];                          ///< Ed25519 signature of the measurement.

  /* parameters */
  struct runtime_params_t params;                     ///< Parameters passed to the enclave.

  /* enclave execution context */
  unsigned int n_thread;                              ///< Number of active threads.
  struct thread_state threads[MAX_ENCL_THREADS];      ///< Thread state information.

  struct platform_enclave_data ped;                   ///< Platform-specific enclave data.
};

/* attestation reports */
/**
 * @brief Enclave attestation report structure.
 */
struct enclave_report
{
  byte hash[MDSIZE];              ///< Enclave measurement hash.
  uint64_t data_len;              ///< Length of user-provided data.
  byte data[ATTEST_DATA_MAXLEN];  ///< Attested user data.
  byte signature[SIGNATURE_SIZE]; ///< Signature over (hash || data).
};
/**
 * @brief Security Monitor (SM) report structure.
 */
struct sm_report
{
  byte hash[MDSIZE];                ///< SM hash.
  byte public_key[PUBLIC_KEY_SIZE]; ///< SM public key.
  byte signature[SIGNATURE_SIZE];   ///< Signature over hash.
};
/**
 * @brief Combined report structure (enclave + SM).
 */
struct report
{
  struct enclave_report enclave;        ///< Enclave attestation report.
  struct sm_report sm;                  ///< SM attestation report.
  byte dev_public_key[PUBLIC_KEY_SIZE]; ///< Developer public key (non-SM).
};

/* sealing key structure */
/**
 * @brief Size (in bytes) of the sealing key used by enclaves.
 */
#define SEALING_KEY_SIZE 128

/**
 * @brief Sealing key structure for persistent enclave-specific secrets.
 */
struct sealing_key
{
  uint8_t key[SEALING_KEY_SIZE];     ///< Sealing key.
  uint8_t signature[SIGNATURE_SIZE]; ///< Signature for integrity/authentication.
};

/*** SBI functions & external functions ***/
// callables from the host
/**
 * @brief Create a new enclave.
 *
 * @param eid Pointer to store the created enclave ID.
 * @param create_args Pointer to SBI creation arguments.
 * @return 0 on success, error code otherwise.
 */
unsigned long create_enclave(unsigned long *eid, struct keystone_sbi_create_t create_args);
/**
 * @brief Destroy an existing enclave.
 *
 * @param eid Enclave ID to destroy.
 * @return 0 on success, error code otherwise.
 */
unsigned long destroy_enclave(enclave_id eid);
/**
 * @brief Run an enclave.
 *
 * @param regs Pointer to trap registers.
 * @param eid Enclave ID to run.
 * @return 0 on success, error code otherwise.
 */
unsigned long run_enclave(struct sbi_trap_regs *regs, enclave_id eid);
/**
 * @brief Resume execution of a stopped enclave.
 *
 * @param regs Pointer to trap registers.
 * @param eid Enclave ID to resume.
 * @return 0 on success, error code otherwise.
 */
unsigned long resume_enclave(struct sbi_trap_regs *regs, enclave_id eid);
// callables from the enclave
/**
 * @brief Exit the enclave and return to the host.
 *
 * @param regs Pointer to trap registers.
 * @param eid Enclave ID.
 * @return 0 on success, error code otherwise.
 */
unsigned long exit_enclave(struct sbi_trap_regs *regs, enclave_id eid);
/**
 * @brief Stop enclave execution voluntarily.
 *
 * @param regs Pointer to trap registers.
 * @param request Stop reason code.
 * @param eid Enclave ID.
 * @return 0 on success, error code otherwise.
 */
unsigned long stop_enclave(struct sbi_trap_regs *regs, uint64_t request, enclave_id eid);
/**
 * @brief Generate an attestation report for the enclave.
 *
 * @param report Destination pointer in enclave memory.
 * @param data Pointer to additional user data.
 * @param size Length of the user data.
 * @param eid Enclave ID.
 * @return 0 on success, error code otherwise.
 */
unsigned long attest_enclave(uintptr_t report, uintptr_t data, uintptr_t size, enclave_id eid);
// attestation
/**
 * @brief Validate enclave memory and calculate its hash.
 *
 * @param enclave Pointer to the enclave metadata structure.
 * @return 0 on success, error code otherwise.
 */
unsigned long validate_and_hash_enclave(struct enclave* enclave);
// TODO: These functions are supposed to be internal functions.
/**
 * @brief Initialize enclave metadata structures.
 */
void enclave_init_metadata(void);
/**
 * @brief Copy user-provided enclave creation arguments.
 *
 * @param src Pointer to source arguments (in user memory).
 * @param dest Pointer to destination struct in SM memory.
 * @return 0 on success, error code otherwise.
 */
unsigned long copy_enclave_create_args(uintptr_t src, struct keystone_sbi_create_t* dest);

/**
 * @brief Get index of an enclave region by type.
 *
 * @param eid Enclave ID.
 * @param type Desired region type.
 * @return Index of region or -1 if not found.
 */
int get_enclave_region_index(enclave_id eid, enum enclave_region_type type);
/**
 * @brief Get base physical address of a region.
 *
 * @param eid Enclave ID.
 * @param memid Memory region index.
 * @return Base address or 0 on failure.
 */
uintptr_t get_enclave_region_base(enclave_id eid, int memid);
/**
 * @brief Get size of a memory region.
 *
 * @param eid Enclave ID.
 * @param memid Memory region index.
 * @return Size in bytes or 0 on failure.
 */
uintptr_t get_enclave_region_size(enclave_id eid, int memid);
/**
 * @brief Derive and return the sealing key for the enclave.
 *
 * @param seal_key Pointer to destination buffer.
 * @param key_ident Pointer to enclave-specific identity.
 * @param key_ident_size Size of identity buffer.
 * @param eid Enclave ID.
 * @return 0 on success, error code otherwise.
 */
unsigned long get_sealing_key(uintptr_t seal_key, uintptr_t key_ident, size_t key_ident_size, enclave_id eid);
// interrupt handlers
/**
 * @brief Trap handler for enclave-related SBI calls.
 *
 * @param regs Pointer to trap registers.
 */
void sbi_trap_handler_keystone_enclave(struct sbi_trap_regs *regs);
#endif
