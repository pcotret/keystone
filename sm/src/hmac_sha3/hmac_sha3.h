/**
 * @file hmac_sha3.h
 * @brief Header file for HMAC-SHA3 implementation.
 * 
 * This file defines the interface for the HMAC-SHA3 (Hashed Message Authentication
 * Code with SHA3) cryptographic algorithm, which combines SHA3 with a secret key
 * to provide message authentication. It includes function prototypes for initializing,
 * updating, and finalizing the HMAC operation using the SHA3 family of hash functions.
 */
/*
 *  Copyright (C) 2020 Fraunhofer AISEC
 *  Authors: Benedikt Kopf <benedikt.kopf@aisec.fraunhofer.de>
 *           Lukas Auer <lukas.auer@aisec.fraunhofer.de>
 *           Mathias Morbitzer <mathias.morbitzer@aisec.fraunhofer.de>
 *
 *  hmac_sha3.h
 *
 *  All Rights Reserved. See LICENSE for license details.
 */

#ifndef HMAC_SHA3_H
#define HMAC_SHA3_H

#include "../sha3/sha3.h"

/**
 * @def SHA3_512_BLOCK_LEN
 * @brief Internal block length of SHA3-512 in bytes.
 *
 * This value defines the size of the input block processed at each step of the SHA3-512 hash function.
 */
#define SHA3_512_BLOCK_LEN 72
/**
 * @def SHA3_512_HASH_LEN
 * @brief Output hash length of SHA3-512 in bytes.
 *
 * This value defines the size of the final output hash produced by the SHA3-512 algorithm.
 */
#define SHA3_512_HASH_LEN 64

/**
 * @struct hmac_sha3_ctx_t
 * @brief Context structure for HMAC-SHA3.
 * 
 * This structure holds the SHA3 context and the key used in the HMAC operation.
 */
typedef struct {
    sha3_ctx_t sha3_ctx;                /**< SHA3 context for the HMAC operation. */
    unsigned char key[SHA3_512_BLOCK_LEN]; /**< The secret key used in HMAC, padded to the block length of SHA3-512. */
} hmac_sha3_ctx_t;

/**
 * @brief Computes the HMAC-SHA3 hash of a message.
 * 
 * This function computes the HMAC-SHA3 hash for a given message and secret key.
 * It initializes the context, updates it with the message, and produces the final hash.
 * 
 * @param key The secret key used for HMAC.
 * @param key_len The length of the secret key.
 * @param text The input message to hash.
 * @param text_len The length of the input message.
 * @param hash The resulting HMAC-SHA3 hash.
 */
void hmac_sha3(const unsigned char *key, int key_len,
               const unsigned char *text, int text_len, unsigned char *hash);
/**
 * @brief Initializes the HMAC-SHA3 context.
 * 
 * This function initializes the HMAC-SHA3 context with the secret key. It must
 * be called before using the `hmac_sha3_update` and `hmac_sha3_final` functions.
 * 
 * @param ctx The HMAC-SHA3 context to initialize.
 * @param key The secret key used for HMAC.
 * @param key_len The length of the secret key.
 */
void hmac_sha3_init(hmac_sha3_ctx_t *ctx,
                    const unsigned char *key, int key_len);
/**
 * @brief Updates the HMAC-SHA3 context with more data.
 * 
 * This function updates the HMAC-SHA3 context with additional data to be included
 * in the HMAC hash. It can be called multiple times before calling `hmac_sha3_final`.
 * 
 * @param ctx The HMAC-SHA3 context.
 * @param text The input message to hash.
 * @param text_len The length of the input message.
 */
void hmac_sha3_update(hmac_sha3_ctx_t *ctx,
                      const unsigned char *text, int text_len);

/**
 * @brief Finalizes the HMAC-SHA3 computation and produces the hash.
 * 
 * This function finalizes the HMAC-SHA3 operation and stores the resulting hash
 * in the provided buffer.
 * 
 * @param ctx The HMAC-SHA3 context.
 * @param hash The resulting HMAC-SHA3 hash.
 */
void hmac_sha3_final(hmac_sha3_ctx_t *ctx, unsigned char *hash);

#endif /* HMAC_SHA3_H */
