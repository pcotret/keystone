/**
 * @file sm.h
 * @brief Main interface for Keystone Secure Monitor (SM) core functionality.
 */
//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
#ifndef sm_h
#define sm_h

#include <sbi/sbi_types.h>
#include "pmp.h"
#include "sm-sbi.h"
#include <sbi/riscv_encoding.h>

#include "sm_call.h"
#include "sm_err.h"

/**
 * @brief Initialize the Secure Monitor.
 * @param cold_boot Indicates whether this is a cold boot initialization.
 */
void sm_init(bool cold_boot);

/* Platform-specific functions */
#define ATTESTATION_KEY_LENGTH 64  /**< Length of attestation public key in bytes. */
/**
 * @brief Retrieve the SM's attestation public key.
 * @param dest Pointer to buffer where the key will be written.
 */
void sm_retrieve_pubkey(void* dest);

/**
 * @brief Sign a message using the SM's attestation key.
 * @param sign Output buffer for signature.
 * @param data Input message to sign.
 * @param len Length of the message in bytes.
 */
void sm_sign(void* sign, const void* data, size_t len);

/**
 * @brief Derive a sealing key for the calling enclave.
 * @param key Output buffer for the derived key.
 * @param key_ident Identifier for the key (e.g., namespace or purpose).
 * @param key_ident_size Length of the identifier.
 * @param enclave_hash Hash of the enclave requesting the key.
 * @return 0 on success, negative error code otherwise.
 */
int sm_derive_sealing_key(unsigned char *key,
                          const unsigned char *key_ident,
                          size_t key_ident_size,
                          const unsigned char *enclave_hash);
/**
 * @brief Set PMP permissions for the OS memory region.
 * @param perm PMP permission flags.
 * @return 0 on success, negative error code otherwise.
 */
int osm_pmp_set(uint8_t perm);
#endif
