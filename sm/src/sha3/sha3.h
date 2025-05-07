/**
 * @file sha3.h
 * @brief SHA-3 (Keccak) cryptographic hash function interface.
 *
 * This header defines an implementation of the SHA-3 (Keccak) cryptographic
 * hash functions, including initialization, update, and finalization routines.
 * It also includes a direct hash interface for computing hashes in a single call.
 */
// sha3.h
// 19-Nov-11  Markku-Juhani O. Saarinen <mjos@iki.fi>

#ifndef SHA3_H
#define SHA3_H

#ifdef __riscv_xlen
#include <sbi/sbi_types.h>
#else
#include <stdint.h>
#include <stddef.h>
#endif

#ifndef KECCAKF_ROUNDS
/// Number of Keccak-f rounds (24 as per specification).
#define KECCAKF_ROUNDS 24
#endif

#ifndef ROTL64
/// Rotate left macro for 64-bit values.
#define ROTL64(x, y) (((x) << (y)) | ((x) >> (64 - (y))))
#endif

// state context
/**
 * @struct sha3_ctx_t
 * @brief SHA-3 hashing context structure.
 *
 * This structure holds the internal state of the Keccak permutation and
 * associated parameters used during the hashing process.
 */
typedef struct {
    /**
     * @brief Internal Keccak state buffer.
     *
     * Used as a 200-byte array or 25-element array of 64-bit words.
     * These represent the same state data in two different views.
     */
    union {                                 // state:
        uint8_t b[200]; /**< State as bytes. */
        uint64_t q[25]; /**< State as 64-bit words. */
    } st;
    int pt;             /**< Current position in buffer. */
    int rsiz;           /**< Rate size in bytes. */
    int mdlen;          /**< Message digest length in bytes. */
} sha3_ctx_t;

// Compression function.
/**
 * @brief Keccak-f[1600] permutation.
 *
 * @param st 25-element array of 64-bit words representing the Keccak state.
 */
void sha3_keccakf(uint64_t st[25]);

// OpenSSL - like interfece
/**
 * @brief Initialize SHA-3 hashing context.
 *
 * @param c Pointer to the SHA-3 context.
 * @param mdlen Desired digest length in bytes (e.g., 32 for SHA3-256).
 * @return 0 on success, non-zero on error.
 */
int sha3_init(sha3_ctx_t *c, int mdlen);    // mdlen = hash output in bytes
/**
 * @brief Update SHA-3 context with input data.
 *
 * @param c Pointer to the SHA-3 context.
 * @param data Pointer to the input data.
 * @param len Length of input data in bytes.
 * @return 0 on success, non-zero on error.
 */
int sha3_update(sha3_ctx_t *c, const void *data, size_t len);
/**
 * @brief Finalize SHA-3 computation and retrieve the digest.
 *
 * @param md Pointer to the output buffer where the digest will be written.
 * @param c Pointer to the SHA-3 context.
 * @return 0 on success, non-zero on error.
 */
int sha3_final(void *md, sha3_ctx_t *c);    // digest goes to md

// compute a sha3 hash (md) of given byte length from "in"

/**
 * @brief Compute SHA-3 hash in one call.
 *
 * @param in Pointer to the input data.
 * @param inlen Length of input data in bytes.
 * @param md Pointer to the output buffer for the digest.
 * @param mdlen Desired digest length in bytes.
 * @return Pointer to the output buffer (md).
 */
void *sha3(const void *in, size_t inlen, void *md, int mdlen);

#endif

