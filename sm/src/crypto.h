/**
 * @file crypto.h
 * @brief Cryptographic interface using SHA3, Ed25519, and HKDF with SHA3-512.
 *
 * Provides functions for hashing, signing, and key derivation.
 */
//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
#ifndef __CRYPTO_H__
#define __CRYPTO_H__

#include <sbi/sbi_types.h>
#include "sha3/sha3.h"
#include "ed25519/ed25519.h"
#include "hkdf_sha3_512/hkdf_sha3_512.h"

/** @brief Typedef for the hash context (based on SHA3). */
typedef sha3_ctx_t hash_ctx;
#define MDSIZE  64          /**< Output size of the hash (in bytes). */
#define SIGNATURE_SIZE  64  /**< Ed25519 signature size. */
#define PRIVATE_KEY_SIZE  64 /**< Private key size (includes public key). */
#define PUBLIC_KEY_SIZE 32  /**< Public key size. */

/** @brief Byte type alias. */
typedef unsigned char byte;

/** @brief Global storage for SM hash value. */
extern byte sm_hash[MDSIZE];
/** @brief Global storage for SM signature. */
extern byte sm_signature[SIGNATURE_SIZE];
/** @brief Global storage for SM public key. */
extern byte sm_public_key[PUBLIC_KEY_SIZE];
/** @brief Global storage for SM private key. */
extern byte sm_private_key[PRIVATE_KEY_SIZE];
/**
 * @brief Initialize a hash context.
 * @param hash_ctx Pointer to hash context.
 */
void hash_init(hash_ctx* hash_ctx);
/**
 * @brief Extend the hash with arbitrary data.
 * @param hash_ctx Pointer to hash context.
 * @param ptr Data to hash.
 * @param len Length of data.
 */
void hash_extend(hash_ctx* hash_ctx, const void* ptr, size_t len);
/**
 * @brief Extend the hash with a full memory page.
 * @param hash_ctx Pointer to hash context.
 * @param ptr Page-aligned data pointer.
 */
void hash_extend_page(hash_ctx* hash_ctx, const void* ptr);
/**
 * @brief Finalize the hash computation.
 * @param md Output digest.
 * @param hash_ctx Hash context to finalize.
 */
void hash_finalize(void* md, hash_ctx* hash_ctx);
/**
 * @brief Generate a digital signature.
 * @param sign Output buffer for signature.
 * @param data Input data to sign.
 * @param len Length of input data.
 * @param public_key Signer's public key.
 * @param private_key Signer's private key.
 */
void sign(void* sign, const void* data, size_t len, const byte* public_key, const byte* private_key);

/**
 * @brief Perform key derivation using HKDF-SHA3-512.
 * @param salt Optional salt value.
 * @param salt_len Length of salt.
 * @param ikm Input keying material.
 * @param ikm_len Length of input keying material.
 * @param info Optional context and application specific information.
 * @param info_len Length of info.
 * @param okm Output keying material.
 * @param okm_len Length of output keying material.
 * @return 0 on success, or error code.
 */
int kdf(const unsigned char* salt, size_t salt_len,
        const unsigned char* ikm, size_t ikm_len,
        const unsigned char* info, size_t info_len,
        unsigned char* okm, size_t okm_len);
#endif /* crypto.h */
