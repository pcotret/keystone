/**
 * @file sha256.h
 * @brief API for the SHA-256 cryptographic hash function.
 *
 * This header defines the interface and data structures for computing
 * SHA-256 hashes, including initialization, update, and finalization.
 */
/*********************************************************************
 * Filename:   sha256.h
 * Author:     Brad Conte (brad AT bradconte.com)
 * Copyright:
 * Disclaimer: This code is presented "as is" without any guarantees.
 * Details:    Defines the API for the corresponding SHA1 implementation.
 *********************************************************************/

#ifndef SHA256_H
#define SHA256_H

/*************************** HEADER FILES ***************************/
#include <stddef.h>

/****************************** MACROS ******************************/
/**
 * @def SHA256_BLOCK_SIZE
 * @brief SHA-256 outputs a 32-byte (256-bit) digest.
 */
#define SHA256_BLOCK_SIZE 32  // SHA256 outputs a 32 byte digest

/**************************** DATA TYPES ****************************/

typedef unsigned char BYTE;  /**< Defines an 8-bit unsigned byte. */
typedef unsigned int WORD;  /**< Defines a 32-bit unsigned word. */

/**
 * @struct SHA256_CTX
 * @brief Context structure for SHA-256 computation.
 *
 * Holds intermediate data, state, and length counters used throughout
 * the SHA-256 hashing process.
 */
typedef struct {
  BYTE data[64];             /**< Input data buffer. */
  WORD datalen;              /**< Current length of data in the buffer. */
  unsigned long long bitlen; /**< Total number of bits processed. */
  WORD state[8];             /**< Current hash state (8 32-bit words). */
} SHA256_CTX;

/*********************** FUNCTION DECLARATIONS **********************/
/**
 * @brief Initializes a SHA256_CTX structure.
 * @param ctx Pointer to the SHA256 context to initialize.
 */
void
sha256_init(SHA256_CTX* ctx);
/**
 * @brief Feeds data into the SHA-256 hash.
 * @param ctx Pointer to SHA256 context.
 * @param data Input data to hash.
 * @param len Length of the input data in bytes.
 */
void
sha256_update(SHA256_CTX* ctx, const BYTE data[], size_t len);
/**
 * @brief Finalizes the hash and outputs the digest.
 * @param ctx Pointer to SHA256 context.
 * @param hash Output buffer (must be at least SHA256_BLOCK_SIZE bytes).
 */
void
sha256_final(SHA256_CTX* ctx, BYTE hash[]);

#endif  // SHA256_H
