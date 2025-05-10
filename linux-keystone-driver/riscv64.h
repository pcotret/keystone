/**
 * @file riscv64.h
 * @brief RISC-V 64-bit MMU definitions and helpers for page table management.
 */
#ifndef __RISCV64__
#define __RISCV64__

#include <asm/page.h>
#include <linux/types.h>

/** @brief Insert a bitfield value into a bitmask. */
#define INSERT_FIELD(val, which, fieldval) (((val) & ~(which)) | ((fieldval) * ((which) & ~((which)-1))))

/** @brief RISC-V privilege levels. */
#define PRV_U 0  ///< User privilege level
#define PRV_S 1  ///< Supervisor privilege level
#define PRV_H 2  ///< Hypervisor privilege level (reserved)
#define PRV_M 3  ///< Machine privilege level

#define SATP32_MODE 0x80000000              ///< SATP mode bit for SV32
#define SATP32_ASID 0x7FC00000              ///< ASID field for SATP in SV32
#define SATP32_PPN  0x003FFFFF              ///< PPN field for SATP in SV32
#define SATP64_MODE 0xF000000000000000      ///< SATP mode field mask for SV39/48/57
#define SATP64_ASID 0x0FFFF00000000000      ///< ASID field mask for SV39/48/57
#define SATP64_PPN  0x00000FFFFFFFFFFF      ///< PPN field mask for SV39/48/57

#define SATP_MODE_OFF  0  ///< Bare mode (no translation)
#define SATP_MODE_SV32 1  ///< 32-bit page table mode
#define SATP_MODE_SV39 8  ///< 39-bit virtual addressing (3-level)
#define SATP_MODE_SV48 9  ///< 48-bit virtual addressing (4-level)
#define SATP_MODE_SV57 10 ///< 57-bit virtual addressing (5-level)
#define SATP_MODE_SV64 11 ///< 64-bit virtual addressing (reserved)



// page table entry (PTE) fields
#define PTE_V     0x001 ///< PTE valid bit
#define PTE_R     0x002 ///< PTE readable bit
#define PTE_W     0x004 ///< PTE writable bit
#define PTE_X     0x008 ///< PTE executable bit
#define PTE_U     0x010 ///< PTE user-accessible bit
#define PTE_G     0x020 ///< PTE global mapping bit
#define PTE_A     0x040 ///< PTE accessed bit
#define PTE_D     0x080 ///< PTE dirty bit
#define PTE_SOFT  0x300 ///< PTE software-reserved bits

#define PTE_PPN_SHIFT 10 ///< Bit position where the PPN starts in a PTE

#define PTE_TABLE(PTE) (((PTE) & (PTE_V | PTE_R | PTE_W | PTE_X)) == PTE_V) ///< Check if PTE is a page table pointer

#define MSTATUS_SD MSTATUS64_SD ///< mstatus SD bit alias for RV64
#define SSTATUS_SD SSTATUS64_SD ///< sstatus SD bit alias for RV64

#define RISCV_PGLEVEL_BITS 9 ///< Number of bits per page table level
#define RISCV_PGSHIFT 12     ///< Page size shift (2^12 = 4KB)
#define RISCV_PGSIZE (1 << RISCV_PGSHIFT) ///< Standard page size (4KB)

#define MEGAPAGE_SIZE ((uintptr_t)(RISCV_PGSIZE << RISCV_PGLEVEL_BITS)) ///< Size of a megapage (2MB)
#define GIGAPAGE_SIZE (MEGAPAGE_SIZE << RISCV_PGLEVEL_BITS)             ///< Size of a gigapage (1GB)
#define SATP_MODE_CHOICE INSERT_FIELD(0, SATP64_MODE, SATP_MODE_SV39)  ///< Default SATP mode field value for SV39


//extern pte_t* root_page_table;

/**
 * @brief Flush the TLB (Translation Lookaside Buffer).
 */
static inline void flush_tlb(void)
{
  asm volatile ("sfence.vma");
}
/**
 * @brief Create a page table entry.
 * @param ppn Physical page number.
 * @param type PTE flags (e.g., PTE_R | PTE_W).
 * @return A properly formatted PTE.
 */
static inline pte_t pte_create(unsigned long ppn, int type)
{ 
  return __pte( (ppn << PTE_PPN_SHIFT) | PTE_V | type );
}

/**
 * @brief Create a page table descriptor pointing to a next-level page table.
 * @param ppn Physical page number of the next-level page table.
 * @return A valid PTE entry with only the valid bit.
 */
static inline pte_t ptd_create(unsigned long ppn)
{
  return pte_create(ppn, PTE_V);
}
#endif
