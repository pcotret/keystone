/**
 * @file sm-sbi.h
 * @brief SBI call interface for Keystone Secure Monitor (SM) services.
 */
//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
#ifndef _KEYSTONE_SBI_H_
#define _KEYSTONE_SBI_H_

#include <sbi/sbi_types.h>
#include <sbi/sbi_trap.h>


/**
 * @brief Create a new enclave.
 * @param out_val Pointer to store enclave ID.
 * @param create_args Pointer to enclave creation arguments.
 * @return 0 on success, error code otherwise.
 */
unsigned long
sbi_sm_create_enclave(unsigned long *out_val, uintptr_t create_args);

/**
 * @brief Destroy an existing enclave.
 * @param eid Enclave ID.
 * @return 0 on success, error code otherwise.
 */
unsigned long
sbi_sm_destroy_enclave(unsigned long eid);

/**
 * @brief Enter and run the enclave.
 * @param regs Pointer to trap register state.
 * @param eid Enclave ID.
 * @return 0 on success, error code otherwise.
 */
unsigned long
sbi_sm_run_enclave(struct sbi_trap_regs *regs, unsigned long eid);

/**
 * @brief Exit the enclave, returning control to the host.
 * @param regs Pointer to trap register state.
 * @param retval Return value from the enclave.
 * @return 0 on success, error code otherwise.
 */
unsigned long
sbi_sm_exit_enclave(struct sbi_trap_regs *regs, unsigned long retval);

/**
 * @brief Temporarily stop an enclave.
 * @param regs Pointer to trap register state.
 * @param request Reason for stopping.
 * @return 0 on success, error code otherwise.
 */
unsigned long
sbi_sm_stop_enclave(struct sbi_trap_regs *regs, unsigned long request);


/**
 * @brief Resume a previously stopped enclave.
 * @param regs Pointer to trap register state.
 * @param eid Enclave ID.
 * @return 0 on success, error code otherwise.
 */
unsigned long
sbi_sm_resume_enclave(struct sbi_trap_regs *regs, unsigned long eid);

/**
 * @brief Generate attestation report for an enclave.
 * @param report Address to store the report.
 * @param data User data to include in report.
 * @param size Size of the user data.
 * @return 0 on success, error code otherwise.
 */
unsigned long
sbi_sm_attest_enclave(uintptr_t report, uintptr_t data, uintptr_t size);

/**
 * @brief Retrieve a sealing key unique to the enclave and key identifier.
 * @param seal_key Address to store the key.
 * @param key_ident Identifier for the key.
 * @param key_ident_size Size of the identifier.
 * @return 0 on success, error code otherwise.
 */
unsigned long
sbi_sm_get_sealing_key(uintptr_t seal_key, uintptr_t key_ident, size_t key_ident_size);


/**
 * @brief Generate a cryptographically secure random number.
 * @return 64-bit random value.
 */
unsigned long
sbi_sm_random(void);


/**
 * @brief Call a registered plugin within the SM.
 * @param plugin_id Identifier for the plugin.
 * @param call_id Function ID within the plugin.
 * @param arg0 First argument.
 * @param arg1 Second argument.
 * @return Plugin-specific return value.
 */
unsigned long
sbi_sm_call_plugin(uintptr_t plugin_id, uintptr_t call_id, uintptr_t arg0, uintptr_t arg1);

#endif
