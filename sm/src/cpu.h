/** 
 * @file cpu.h
 * @brief CPU context management for enclaves.
 */
//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
#ifndef __CPU_H__
#define __CPU_H__

#include "sm.h"
#include "enclave.h"

/* hart state for regulating SBI */
/**
 * @struct cpu_state
 * @brief Represents the CPU state for enclave context tracking.
 *
 * This structure holds the state of a hart to indicate whether it is currently 
 * executing inside an enclave and, if so, the identifier of the active enclave.
 */
struct cpu_state
{
  int is_enclave; /**< Flag indicating if the CPU is in enclave mode (non-zero if true). */
  enclave_id eid; /**< Identifier of the currently executing enclave. */
};

/* external functions */
/**
 * @brief Checks if the current CPU is in an enclave context.
 *
 * @return Non-zero if in enclave context, 0 otherwise.
 */
int cpu_is_enclave_context(void);
/**
 * @brief Retrieves the enclave ID of the current context.
 *
 * @return The enclave ID if in enclave context, or -1 if not.
 */
int cpu_get_enclave_id(void);
/**
 * @brief Enters enclave context with the given enclave ID.
 *
 * @param eid The enclave ID to enter.
 */
void cpu_enter_enclave_context(enclave_id eid);
/**
 * @brief Exits the current enclave context.
 *
 * Marks the current CPU as no longer running in enclave mode.
 */
void cpu_exit_enclave_context(void);

#endif
