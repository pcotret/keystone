/**
 * @file sbi.h
 * @brief SBI (Supervisor Binary Interface) calls for enclave operations.
 *
 * This header defines the interface for SBI calls used in enclave runtimes,
 * including I/O, timers, memory queries, attestation, and sealing key retrieval.
 */
//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
#ifndef __SBI_H_
#define __SBI_H_

#include <stdint.h>
#include <stddef.h>

#include "sm_call.h"

/**
 * @brief Write a character to the host console.
 * @param c The character to write.
 */
void
sbi_putchar(char c);
/**
 * @brief Set the timer to trigger at the specified time.
 * @param stime_value The time value at which the timer should trigger.
 */
void
sbi_set_timer(uint64_t stime_value);
/**
 * @brief Stop the current enclave and return control to the host.
 * @param request A value indicating the stop request type.
 * @return An implementation-defined status code.
 */
uintptr_t
sbi_stop_enclave(uint64_t request);
/**
 * @brief Exit the current enclave with the specified return value.
 * @param retval The value to return to the host.
 */
void
sbi_exit_enclave(uint64_t retval);
/**
 * @brief Generate a random value using the platform's entropy source.
 * @return A random value.
 */
uintptr_t
sbi_random();
/**
 * @brief Query the size of the multimem region.
 * @param size Pointer to a variable to store the size of the multimem region.
 * @return 0 on success, non-zero on failure.
 */
uintptr_t
sbi_query_multimem(size_t *size);

/**
 * @brief Query the base address of the multimem region.
 * @param addr Pointer to store the base address of the multimem region.
 * @return 0 on success, non-zero on failure.
 */
uintptr_t
sbi_query_multimem_addr(uintptr_t *addr);

/**
 * @brief Generate an attestation report for the enclave.
 * @param report Pointer to the report structure to fill.
 * @param buf Buffer containing data to include in the report.
 * @param len Length of the buffer.
 * @return 0 on success, non-zero on failure.
 */
uintptr_t
sbi_attest_enclave(void* report, void* buf, uintptr_t len);

/**
 * @brief Retrieve the sealing key for the enclave.
 * @param key_struct Pointer to the structure to fill with the key.
 * @param key_ident Pointer to an identifier for the key.
 * @param len Length of the identifier.
 * @return 0 on success, non-zero on failure.
 */
uintptr_t
sbi_get_sealing_key(uintptr_t key_struct, uintptr_t key_ident, uintptr_t len);

#endif
