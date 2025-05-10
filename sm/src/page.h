/**
 * @file page.h
 * @brief Header file defining page table entry (PTE) and related constants for RISC-V architecture.
 */
//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
#ifndef _SM_PAGE_H_
#define _SM_PAGE_H_

#include <sbi/sbi_types.h>
#include <sbi/riscv_encoding.h>
#include <sbi/riscv_asm.h>


#define RISCV_PGSIZE  PAGE_SIZE   /**< Page size. */
#define RISCV_PGSHIFT PAGE_SHIFT  /**< Page shift. */

/* Page Table Entry (PTE) flags */
#define PTE_V     _UL(0x001) /**< Valid. */
#define PTE_R     _UL(0x002) /**< Read. */
#define PTE_W     _UL(0x004) /**< Write. */
#define PTE_X     _UL(0x008) /**< Execute. */
#define PTE_U     _UL(0x010) /**< User-accessible. */
#define PTE_G     _UL(0x020) /**< Global mapping. */
#define PTE_A     _UL(0x040) /**< Accessed. */
#define PTE_D     _UL(0x080) /**< Dirty. */
#define PTE_SOFT  _UL(0x300) /**< Software-reserved bits. */

#if __riscv_xlen == 64
# define RISCV_PGLEVEL_MASK        0x1ff   /**< Page level index mask for RV64. */
# define RISCV_PGTABLE_HIGHEST_BIT 0x100   /**< Highest bit in RV64 page tables. */
# define RISCV_PGLEVEL_BITS        9       /**< Bits per page level in RV64. */
#else
# define RISCV_PGLEVEL_MASK        0x3ff   /**< Page level index mask for RV32. */
# define RISCV_PGTABLE_HIGHEST_BIT 0x300   /**< Highest bit in RV32 page tables. */
# define RISCV_PGLEVEL_BITS        10      /**< Bits per page level in RV32. */
#endif

#define PTE_PPN_SHIFT 10               /**< Shift for physical page number. */

#define VA_BITS        39              /**< Virtual address space size. */
#define RISCV_PGLEVEL_TOP ((VA_BITS - RISCV_PGSHIFT) / RISCV_PGLEVEL_BITS) /**< Top page table level. */
#endif

