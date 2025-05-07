/**
 * @file ipi.h
 * @brief PMP IPI (Physical Memory Protection Inter-Processor Interrupts) support for Keystone.
 */
#ifndef __PMP_IPI_H__
#define __PMP_IPI_H__

#include <sbi/sbi_scratch.h>
#include <sbi/sbi_hartmask.h>
#include <sbi/sbi_tlb.h>

/// PMP IPI type to **set** a PMP region.
#define SBI_PMP_IPI_TYPE_SET    0
/// PMP IPI type to **unset** a PMP region.
#define SBI_PMP_IPI_TYPE_UNSET  1

/**
 * @brief PMP IPI info structure passed between harts.
 *
 * This structure carries the parameters necessary to apply PMP changes
 * on remote harts via an IPI.
 */
struct sbi_pmp_ipi_info {
  unsigned long type;    ///< Operation type: SBI_PMP_IPI_TYPE_SET or SBI_PMP_IPI_TYPE_UNSET
  unsigned long __dummy; ///< Reserved or unused padding for alignment
  unsigned long rid;     ///< PMP region ID
  unsigned long perm;    ///< PMP permissions to apply
};

/**
 * @brief Perform a local PMP update on the current hart.
 *
 * @param info TLB shootdown info structure that includes PMP IPI info.
 */
void sbi_pmp_ipi_local_update(struct sbi_tlb_info *info);

/// Size of the PMP IPI info structure.
#define SBI_PMP_IPI_INFO_SIZE sizeof(struct sbi_pmp_ipi_info)

/**
 * @brief Initialize PMP IPI subsystem.
 *
 * @param scratch Pointer to SBI scratch area for the current hart.
 * @param cold_boot True if this is the first boot, false for warm boot.
 * @return 0 on success, or a negative error code.
 */
int sbi_pmp_ipi_init(struct sbi_scratch* scratch, bool cold_boot);

/**
 * @brief Send a PMP IPI request to a group of harts.
 *
 * @param hmask Bitmask of target harts.
 * @param hbase Hart base index (typically 0).
 * @param info Pointer to PMP IPI info structure.
 * @return 0 on success, or a negative error code.
 */
int sbi_pmp_ipi_request(ulong hmask, ulong hbase, struct sbi_pmp_ipi_info* info);

/**
 * @brief Helper to send a PMP IPI and wait for all target harts to complete the operation.
 *
 * @param region_idx Region ID to modify.
 * @param type Type of operation (SBI_PMP_IPI_TYPE_SET or SBI_PMP_IPI_TYPE_UNSET).
 * @param perm Permissions to assign to the region.
 */
void send_and_sync_pmp_ipi(int region_idx, int type, uint8_t perm);
#endif
