/**
 * @file platform-hook.h
 * @brief Platform-specific hook declarations for enclave lifecycle and system integration.
 */
#ifndef _PLATFORM_HOOK_H_
#define _PLATFORM_HOOK_H_

#include "enclave.h"

/* These functions are defined by platform/soc specific objects,
   defined in platform/$PLATFORM/$PLATFORM.c */

/* This fires once FOR EACH sm supported enclave during init of
   enclave metadata. It may not fail currently. */

/**
 * @brief Initialize metadata for a single enclave. Called once per enclave.
 * @param enclave Pointer to the enclave being initialized.
 */
void platform_init_enclave(struct enclave* enclave);

/* This fires once GLOBALLY before any other platform init */
/**
 * @brief Perform global one-time platform initialization. Runs before any other hook.
 * @return Implementation-defined status or capability flags.
 */
unsigned long platform_init_global_once(void);
/* Fires once per-hart after global_once */
/**
 * @brief Perform per-hart platform initialization. Called once per hart.
 * @return Implementation-defined status or capability flags.
 */
unsigned long platform_init_global(void);

/* This fires once each time an enclave is created by the sm */
/**
 * @brief Hook called when an enclave is created.
 * @param enclave Pointer to the created enclave.
 * @return Implementation-defined result.
 */
unsigned long platform_create_enclave(struct enclave* enclave);

/* This fires once each time an enclave is destroyed by the sm */
/**
 * @brief Hook called when an enclave is destroyed.
 * @param enclave Pointer to the destroyed enclave.
 */
void platform_destroy_enclave(struct enclave* enclave);

/* This fires when context switching INTO an enclave from the OS */
/**
 * @brief Hook called when switching into an enclave from the OS.
 * @param enclave Pointer to the enclave being entered.
 */
void platform_switch_to_enclave(struct enclave* enclave);

/* This fires when context switching OUT of an enclave into the OS */
/**
 * @brief Hook called when switching out of an enclave to the OS.
 * @param enclave Pointer to the enclave being exited.
 */
void platform_switch_from_enclave(struct enclave* enclave);

/* Future version: This fires when context switching from enclave A to
   enclave B */
// void platform_switch_between_enclaves(platform_enclave_data* enclaveA,
//                                       platform_enclave_data* enclaveB);

/* This is a required feature, it must return 64bits of random data on
   demand and never fail. If it would fail it may power off
   instead. */
/**
 * @brief Returns 64 bits of random data. Must never fail.
 * @return 64-bit cryptographically secure random value.
 */
uint64_t platform_random(void);

#endif /* _PLATFORM_HOOK_H_ */
