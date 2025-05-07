/**
 * @file platform.c
 * @brief Platform-specific functions for enclave management and random number generation.
 *
 * This file defines a set of functions that interact with the underlying platform
 * to manage enclaves and generate random numbers. These functions are part of the
 * Secure Monitor (SM) interface and are required for setting up, switching, and 
 * destroying enclaves. It also includes functionality for secure random number
 * generation using platform-provided services.
 * 
 * The functions include:
 * - Enclave lifecycle management: create, switch to, switch from, initialize, and destroy.
 * - Random number generation: retrieves secure 64-bit random values.
 * - Secure key management: copying and zeroing out sensitive data such as public keys and signatures.
 * 
 * This file assumes that the platform supports specific services for enclave 
 * management and random number generation.
 */
#include "platform-hook.h"
#include "enclave.h"
#include <mss_sys_services.h>
#include <sbi/riscv_locks.h>
#include <sbi/sbi_string.h>
#include <sm_assert.h>

/**
 * @brief Initializes global platform state once.
 * 
 * This function initializes platform-specific state that is required to 
 * run the system. It should be called once during system boot.
 * 
 * @return SBI_ERR_SM_ENCLAVE_SUCCESS if successful, error code otherwise.
 */
unsigned long platform_init_global_once(void){
  return SBI_ERR_SM_ENCLAVE_SUCCESS;
}

/**
 * @brief Initializes global platform state.
 * 
 * This function initializes global platform-specific state.
 * 
 * @return SBI_ERR_SM_ENCLAVE_SUCCESS if successful, error code otherwise.
 */
unsigned long platform_init_global(void){
  return SBI_ERR_SM_ENCLAVE_SUCCESS;
}

/**
 * @brief Initializes the enclave on the platform.
 * 
 * This function prepares the platform to create and manage an enclave, 
 * but does not create the enclave itself. 
 * 
 * @param enclave Pointer to the enclave structure to initialize.
 */
void platform_init_enclave(struct enclave* enclave){
  return;
}

/**
 * @brief Destroys the enclave on the platform.
 * 
 * This function cleans up platform-specific state associated with 
 * the provided enclave.
 * 
 * @param enclave Pointer to the enclave structure to destroy.
 */
void platform_destroy_enclave(struct enclave* enclave){
  return;
}

/**
 * @brief Creates an enclave on the platform.
 * 
 * This function creates a new enclave on the platform, initializing 
 * the necessary platform state and resources.
 * 
 * @param enclave Pointer to the enclave structure to create.
 * @return SBI_ERR_SM_ENCLAVE_SUCCESS if successful, error code otherwise.
 */
unsigned long platform_create_enclave(struct enclave* enclave){
  return SBI_ERR_SM_ENCLAVE_SUCCESS;
}

/**
 * @brief Switches the context to the provided enclave.
 * 
 * This function transitions the platform's execution context to 
 * the provided enclave. It may perform necessary platform-specific 
 * setup for the enclave.
 * 
 * @param enclave Pointer to the enclave structure to switch to.
 */
void platform_switch_to_enclave(struct enclave* enclave){
  return;
}

/**
 * @brief Switches the context from the provided enclave.
 * 
 * This function transitions the platform's execution context from 
 * the provided enclave back to the normal execution context.
 * 
 * @param enclave Pointer to the enclave structure to switch from.
 */
void platform_switch_from_enclave(struct enclave* enclave){
  return;
}

#define NONCE_BYTES (256/8)                             ///< Number of bytes in the nonce (256 bits)
#define RAND_STATE_WORDS (NONCE_BYTES/sizeof(uint64_t)) ///< Number of 64-bit words in random state
/**
 * @struct random
 * @brief Structure representing the state of random number generation.
 * 
 * This structure holds the random data state, including a buffer and 
 * the count of remaining words to be returned.
 */
struct random {
  uint64_t data[RAND_STATE_WORDS]; ///< Buffer to hold random data.
  uint8_t words_left;              ///< Number of remaining 64-bit words to return.
};
/// Spinlock used to synchronize access to random state.
static spinlock_t rand_state_lock = SPIN_LOCK_INITIALIZER;
/// Global random state structure.
static struct random rand_state;

/**
 * @brief Retrieves a 64-bit random value.
 * 
 * This function fetches a 64-bit random value, possibly using 
 * platform-specific services. If the random state buffer is empty, 
 * it requests a new set of random words.
 * 
 * @return A 64-bit random number.
 */
uint64_t platform_random(void){
  spin_lock(&rand_state_lock);

  if (!rand_state.words_left) {
    // This service provides 256 bits of real random data
    // It might be a bit slow to query though.
    int ret = MSS_SYS_nonce_service((uint8_t *)&rand_state.data, 0);
    sm_assert(ret == 0);
    rand_state.words_left = RAND_STATE_WORDS;
  }
  uint64_t out = rand_state.data[--rand_state.words_left];

  spin_unlock(&rand_state_lock);
  return out;
}

// Initialization functions
/// Developer's public key.
extern byte dev_public_key[PUBLIC_KEY_SIZE];

// Todo secure boot
/**
 * @brief Clears sensitive data such as keys and hashes.
 * 
 * This function securely zeroes out sensitive data in the system,
 * including hashes and keys. This is typically done during secure boot
 * or cleanup.
 */
void sm_copy_key(void)
{
  sbi_memset(sm_hash, 0, MDSIZE);
  sbi_memset(sm_signature, 0, SIGNATURE_SIZE);
  sbi_memset(sm_public_key, 0, PUBLIC_KEY_SIZE);
  sbi_memset(sm_private_key, 0, PRIVATE_KEY_SIZE);
  sbi_memset(dev_public_key, 0, PUBLIC_KEY_SIZE);
}
