/**
 * @file keystone-sbi.h
 * @brief Keystone SBI (Supervisory Binary Interface) declarations.
 * 
 * This file contains the function declarations for interacting with the
 * Keystone SBI (Supervisory Binary Interface), which is used for managing
 * enclaves in the Keystone secure enclave framework.
 */
//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
#ifndef _KEYSTONE_SBI_
#define _KEYSTONE_SBI_

#include "keystone_user.h"
#include "sm_call.h"

#include <asm/sbi.h>

/**
 * @brief Creates a new enclave via the SBI.
 *
 * This function invokes the SBI to create a new enclave using the specified
 * creation parameters.
 *
 * @param args The creation parameters for the new enclave.
 * @return The result of the creation operation, encapsulated in an sbiret structure.
 */
struct sbiret sbi_sm_create_enclave(struct keystone_sbi_create_t* args);

/**
 * @brief Destroys an existing enclave.
 *
 * This function invokes the SBI to destroy the enclave identified by the given
 * enclave ID (eid).
 *
 * @param eid The enclave ID of the enclave to destroy.
 * @return The result of the destroy operation, encapsulated in an sbiret structure.
 */
struct sbiret sbi_sm_destroy_enclave(unsigned long eid);
/**
 * @brief Runs the specified enclave.
 *
 * This function invokes the SBI to run the enclave identified by the given
 * enclave ID (eid).
 *
 * @param eid The enclave ID of the enclave to run.
 * @return The result of the run operation, encapsulated in an sbiret structure.
 */
struct sbiret sbi_sm_run_enclave(unsigned long eid);
/**
 * @brief Resumes the specified enclave.
 *
 * This function invokes the SBI to resume the execution of an enclave that was
 * previously paused, identified by the given enclave ID (eid).
 *
 * @param eid The enclave ID of the enclave to resume.
 * @return The result of the resume operation, encapsulated in an sbiret structure.
 */
struct sbiret sbi_sm_resume_enclave(unsigned long eid);

#endif
