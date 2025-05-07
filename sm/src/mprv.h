/**
 * @file mprv.h
 * @brief Memory copy functions with MPRV support between SM and external world.
 */
#pragma once
#include <sbi/sbi_types.h>

/**
 * @brief Represents a block of memory for fast aligned transfers.
 *
 * The block is composed of 8 register-sized words.
 */
typedef struct {
  size_t words[8];  /**< Array of 8 register-sized words. */
} mprv_block;

/**
 * @brief Copy 1 byte from secure monitor memory to destination.
 *
 * @param dst Destination address (outside SM)
 * @param src Source byte pointer in SM
 * @return 0 on success, non-zero on failure
 */
int copy1_from_sm(uintptr_t dst, const uint8_t *src);
/**
 * @brief Copy one register-sized word from SM.
 *
 * @param dst Destination address
 * @param src Source word pointer in SM
 * @return 0 on success, non-zero on failure
 */
int copy_word_from_sm(uintptr_t dst, const uintptr_t *src);
/**
 * @brief Copy one full `mprv_block` from SM.
 *
 * @param dst Destination address
 * @param src Source block in SM
 * @return 0 on success, non-zero on failure
 */
int copy_block_from_sm(uintptr_t dst, const mprv_block *src);
/**
 * @brief Copy 1 byte to secure monitor memory.
 *
 * @param dst Destination pointer in SM
 * @param src Source address outside SM
 * @return 0 on success, non-zero on failure
 */
int copy1_to_sm(uint8_t *dst, uintptr_t src);
/**
 * @brief Copy one register-sized word to SM.
 *
 * @param dst Destination pointer in SM
 * @param src Source address
 * @return 0 on success, non-zero on failure
 */
int copy_word_to_sm(uintptr_t *dst, uintptr_t src);
/**
 * @brief Copy one full `mprv_block` to SM.
 *
 * @param dst Destination block in SM
 * @param src Source address
 * @return 0 on success, non-zero on failure
 */
int copy_block_to_sm(mprv_block *dst, uintptr_t src);

#if __riscv_xlen == 64
# define STORE    sd
# define LOAD     ld
# define LOG_REGBYTES 3
#elif __riscv_xlen == 32
# define STORE    sw
# define LOAD     lw
# define LOG_REGBYTES 2
#endif

/// Number of bytes per register
#define REGBYTES (1 << LOG_REGBYTES)
/// Size of an `mprv_block` in bytes
#define MPRV_BLOCK (REGBYTES * 8)

/**
 * @brief Copy memory from secure monitor to external destination.
 *
 * This function attempts to copy in large aligned chunks (`mprv_block` or register-sized words)
 * if the source and destination are aligned. Otherwise, falls back to byte-wise copy.
 *
 * @param dst Destination pointer outside SM
 * @param src_buf Source pointer in SM
 * @param len Number of bytes to copy
 * @return 0 on success, non-zero on failure
 */
static inline int copy_from_sm(uintptr_t dst, void *src_buf, size_t len)
{
    uintptr_t src = (uintptr_t)src_buf;

    if (src % REGBYTES  == 0 && dst % REGBYTES == 0) {
        while (len >= MPRV_BLOCK) {
            int res = copy_block_from_sm(dst, (mprv_block *)src);
            if (res)
                return res;

            src += MPRV_BLOCK;
            dst += MPRV_BLOCK;
            len -= MPRV_BLOCK;
        }

        while (len >= REGBYTES) {
            int res = copy_word_from_sm(dst, (uintptr_t *)src);
            if (res)
                return res;

            src += REGBYTES;
            dst += REGBYTES;
            len -= REGBYTES;
        }
    }

    while (len > 0) {
        int res = copy1_from_sm(dst, (uint8_t *)src);
        if (res)
            return res;

        src++;
        dst++;
        len--;
    }

    return 0;
}

/**
 * @brief Copy memory from external source into secure monitor.
 *
 * This function mirrors `copy_from_sm` but in the reverse direction.
 *
 * @param dst_buf Destination pointer in SM
 * @param src Source address outside SM
 * @param len Number of bytes to copy
 * @return 0 on success, non-zero on failure
 */
static inline int copy_to_sm(void *dst_buf, uintptr_t src, size_t len)
{
    uintptr_t dst = (uintptr_t)dst_buf;

    if (src % REGBYTES == 0 && dst % REGBYTES == 0) {
        while (len >= MPRV_BLOCK) {
            int res = copy_block_to_sm((mprv_block *)dst, src);
            if (res)
                return res;

            src += MPRV_BLOCK;
            dst += MPRV_BLOCK;
            len -= MPRV_BLOCK;
        }

        while (len >= REGBYTES) {
            int res = copy_word_to_sm((uintptr_t *)dst, src);
            if (res)
                return res;

            src += REGBYTES;
            dst += REGBYTES;
            len -= REGBYTES;
        }
    }

    while (len > 0) {
        int res = copy1_to_sm((uint8_t *)dst, src);
        if (res)
            return res;

        src++;
        dst++;
        len--;
    }

    return 0;
}
