/**
 * @file pmp.h
 * @brief Physical Memory Protection (PMP) management interface.
 */
//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
#ifndef _PMP_H_
#define _PMP_H_

#include "sm.h"
#include <sbi/riscv_atomic.h>

/** @brief Set bit `n` in `bitmap`. */
#define SET_BIT(bitmap, n) (bitmap |= (0x1 << (n)))
/** @brief Unset bit `n` in `bitmap`. */
#define UNSET_BIT(bitmap, n) (bitmap &= ~(0x1 << (n)))
/** @brief Test if bit `n` is set in `bitmap`. */
#define TEST_BIT(bitmap, n) (bitmap & (0x1 << (n)))

/** @brief PMP region priority levels. */
enum pmp_priority {
  PMP_PRI_ANY,    /**< No specific priority. */
  PMP_PRI_TOP,    /**< Higher priority (placed later in list). */
  PMP_PRI_BOTTOM, /**< Lower priority (placed earlier). */
};

/** @brief All permission bits (Read, Write, Execute). */
#define PMP_ALL_PERM  (PMP_W | PMP_X | PMP_R)
/** @brief No permissions. */
#define PMP_NO_PERM   0

#if __riscv_xlen == 64
/**
 * @def LIST_OF_PMP_REGS
 * @brief List of PMP register and configuration group pairs for RV64.
 *
 * This macro defines the mapping of PMP registers (0–15) to PMP configuration
 * groups, using the macro pattern X(index, group). Each group in RV64 controls
 * 8 PMP entries.
 */
# define LIST_OF_PMP_REGS  X(0,0)  X(1,0)  X(2,0)  X(3,0) \
                           X(4,0)  X(5,0)  X(6,0)  X(7,0) \
                           X(8,2)  X(9,2)  X(10,2) X(11,2) \
                          X(12,2) X(13,2) X(14,2) X(15,2)
/**
 * @def PMP_PER_GROUP
 * @brief Number of PMP entries per configuration group on RV64.
 */
# define PMP_PER_GROUP  8
#else
/**
 * @def LIST_OF_PMP_REGS
 * @brief List of PMP register and configuration group pairs for RV32.
 *
 * Each group in RV32 controls 4 PMP entries.
 */
# define LIST_OF_PMP_REGS  X(0,0)  X(1,0)  X(2,0)  X(3,0) \
                           X(4,1)  X(5,1)  X(6,1)  X(7,1) \
                           X(8,2)  X(9,2)  X(10,2) X(11,2) \
                           X(12,3) X(13,3) X(14,3) X(15,3)
/**
 * @def PMP_PER_GROUP
 * @brief Number of PMP entries per configuration group on RV32.
 */
# define PMP_PER_GROUP  4
#endif

/** @brief Set a PMP register with proper context saving/restoring of mtvec. */
#define PMP_SET(n, g, addr, pmpc) \
{ uintptr_t oldcfg = csr_read(pmpcfg##g); \
  pmpc |= (oldcfg & ~((uintptr_t)0xff << (uintptr_t)8*(n%PMP_PER_GROUP))); \
  asm volatile ("la t0, 1f\n\t" \
                "csrrw t0, mtvec, t0\n\t" \
                "csrw pmpaddr"#n", %0\n\t" \
                "csrw pmpcfg"#g", %1\n\t" \
                "sfence.vma\n\t"\
                ".align 2\n\t" \
                "1: csrw mtvec, t0 \n\t" \
                : : "r" (addr), "r" (pmpc) : "t0"); \
}

/** @brief Unset a PMP register (disable permission). */
#define PMP_UNSET(n, g) \
{ uintptr_t pmpc = csr_read(pmpcfg##g); \
  pmpc &= ~((uintptr_t)0xff << (uintptr_t)8*(n%PMP_PER_GROUP)); \
  asm volatile ("la t0, 1f \n\t" \
                "csrrw t0, mtvec, t0 \n\t" \
                "csrw pmpaddr"#n", %0\n\t" \
                "csrw pmpcfg"#g", %1\n\t" \
                "sfence.vma\n\t"\
                ".align 2\n\t" \
                "1: csrw mtvec, t0" \
                : : "r" (0), "r" (pmpc) : "t0"); \
}

/** @brief Error-handling macro for PMP operations. */
#define PMP_ERROR(error, msg) {\
  sbi_printf("%s:" msg "\n", __func__);\
  return error; \
}

/* PMP IPI mailbox */
/**
 * @struct ipi_msg
 * @brief Structure representing a PMP IPI mailbox message.
 */
struct ipi_msg{
  atomic_t pending; /**< Atomic flag for pending IPI. */
  uint8_t perm;     /**< Permissions to set via IPI. */
};

/* PMP region type */
/**
 * @struct pmp_region
 * @brief Metadata for a PMP region.
 */
struct pmp_region
{
  uint64_t size;     /**< Size of the region. */
  uint8_t addrmode;  /**< Address matching mode (e.g., TOR, NAPOT). */
  uintptr_t addr;    /**< Base address of the region. */
  int allow_overlap; /**< Whether overlapping with other regions is allowed. */
  int reg_idx;       /**< PMP register index assigned to the region. */
};

typedef int pmpreg_id; /**< Type for PMP register index. */
typedef int region_id; /**< Type for PMP region identifier. */

/* external functions */
/**
 * @brief Initialize the PMP subsystem.
 *
 * This function sets up internal data structures for managing PMP regions.
 * It should be called once at boot time.
 */
void pmp_init(void);
/**
 * @brief Initialize a PMP region atomically.
 *
 * This version guarantees atomicity and is safe in concurrent environments.
 *
 * @param start         Start address of the region.
 * @param size          Size of the region in bytes.
 * @param pri           Priority for region placement.
 * @param[out] rid      Pointer to store the assigned region ID.
 * @param allow_overlap Whether to allow overlap with existing regions.
 * @return 0 on success, negative error code on failure.
 */
int pmp_region_init_atomic(uintptr_t start, uint64_t size, enum pmp_priority pri, region_id* rid, int allow_overlap);
/**
 * @brief Initialize a PMP region (non-atomic).
 *
 * Not safe under concurrent access; used when atomicity isn't required.
 *
 * @param start         Start address of the region.
 * @param size          Size of the region in bytes.
 * @param pri           Priority for region placement.
 * @param[out] rid      Pointer to store the assigned region ID.
 * @param allow_overlap Whether to allow overlap with existing regions.
 * @return 0 on success, negative error code on failure.
 */
int pmp_region_init(uintptr_t start, uint64_t size, enum pmp_priority pri, region_id* rid, int allow_overlap);
/**
 * @brief Free a PMP region atomically.
 *
 * @param region Region ID to free.
 * @return 0 on success, negative error code on failure.
 */
int pmp_region_free_atomic(region_id region);
/**
 * @brief Set permissions for a region for a specific enclave.
 *
 * @param n     Region ID.
 * @param perm  Permissions to set (bitmask of PMP_R, PMP_W, PMP_X).
 * @return 0 on success, negative error code on failure.
 */
int pmp_set_keystone(region_id n, uint8_t perm);
/**
 * @brief Set permissions for a region globally (across all contexts).
 *
 * @param n     Region ID.
 * @param perm  Permissions to set.
 * @return 0 on success, negative error code on failure.
 */
int pmp_set_global(region_id n, uint8_t perm);
/**
 * @brief Unset (remove) the PMP region for a specific enclave.
 *
 * @param n Region ID to unset.
 * @return 0 on success, negative error code on failure.
 */
int pmp_unset(region_id n);
/**
 * @brief Unset (remove) the PMP region globally.
 *
 * @param n Region ID to unset.
 * @return 0 on success, negative error code on failure.
 */
int pmp_unset_global(region_id n);
/**
 * @brief Detect if a region overlaps with any existing region (atomically).
 *
 * @param base  Base address of the new region.
 * @param size  Size of the new region.
 * @return 0 if no overlap, non-zero if overlap exists.
 */
int pmp_detect_region_overlap_atomic(uintptr_t base, uintptr_t size);
/**
 * @brief Handle incoming PMP-related inter-processor interrupts (IPIs).
 *
 * Called by secondary harts to synchronize PMP state.
 */
void handle_pmp_ipi(void);
/**
 * @brief Get the base address of a PMP region.
 *
 * @param i Region ID.
 * @return Base address of the region.
 */
uintptr_t pmp_region_get_addr(region_id i);
/**
 * @brief Get the size of a PMP region.
 *
 * @param i Region ID.
 * @return Size of the region in bytes.
 */
uint64_t pmp_region_get_size(region_id i);

#endif
