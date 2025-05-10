/**
 * @file loader-binary.c
 * @brief Memory mapping and runtime loading for the enclave.
 *
 * This file contains the implementation for setting up memory mappings, loading
 * runtime ELF binaries, and mapping untrusted and trusted memory regions.
 */
#include "loader/loader.h"
#include "mm/vm.h"
#include "mm/mm.h"
#include "mm/common.h"
#include "mm/freemem.h"
#include "util/printf.h"
#include <asm/csr.h>



pte root_page_table_storage[BIT(RISCV_PT_INDEX_BITS)] __attribute__((aligned(RISCV_PAGE_SIZE)));

pte load_l2_page_table_storage[BIT(RISCV_PT_INDEX_BITS)] __attribute__((aligned(RISCV_PAGE_SIZE)));

pte load_l3_page_table_storage[BIT(RISCV_PT_INDEX_BITS)] __attribute__((aligned(RISCV_PAGE_SIZE)));

/**
 * @var free_base_final
 * @brief Final base address after memory allocation.
 *
 * This variable holds the final base address after the free memory region 
 * is adjusted for memory allocations during the runtime loading process.
 */
uintptr_t free_base_final = 0;

/**
 * @brief Constructs the SATP register value for page table address.
 * 
 * This function generates the SATP register value by setting the mode and 
 * shifting the physical address (pa) to the correct page table index.
 *
 * @param pa The physical address of the page table.
 * @return The constructed SATP register value.
 */
uintptr_t satp_new(uintptr_t pa)
{
  return (SATP_MODE | (pa >> RISCV_PAGE_BITS));
}
/**
 * @brief Maps the physical memory for loading.
 *
 * This function maps a specified range of physical memory to the virtual address
 * space of the enclave. It ensures that the loading process does not overwrite
 * kernel memory addresses.
 *
 * @param dram_base The base address of the DRAM.
 * @param dram_size The size of the DRAM.
 */
void map_physical_memory(uintptr_t dram_base, uintptr_t dram_size) {
  uintptr_t ptr = EYRIE_LOAD_START;
  /* load address should not override kernel address */
  assert(RISCV_GET_PT_INDEX(ptr, 1) != RISCV_GET_PT_INDEX(RUNTIME_VA_START, 1));
  map_with_reserved_page_table(dram_base, dram_size,
      ptr, load_l2_page_table_storage, load_l3_page_table_storage);
}

/**
 * @brief Maps untrusted memory into the enclave.
 *
 * This function maps the specified untrusted memory into the enclave’s virtual address
 * space, allowing the enclave to access untrusted regions.
 *
 * @param untrusted_ptr The base address of the untrusted memory.
 * @param untrusted_size The size of the untrusted memory.
 * @return 0 on success, -1 on failure.
 */
int map_untrusted_memory(uintptr_t untrusted_ptr, uintptr_t untrusted_size) {
  uintptr_t va        = EYRIE_UNTRUSTED_START;
  while (va < EYRIE_UNTRUSTED_START + untrusted_size) {
    if (!map_page(vpn(va), ppn(untrusted_ptr), PTE_W | PTE_R | PTE_D)) {
      return -1;
    }
    va += RISCV_PAGE_SIZE;
    untrusted_ptr += RISCV_PAGE_SIZE;
  }
  return 0;
}
/**
 * @brief Loads the runtime ELF file and maps memory for the enclave.
 *
 * This function is responsible for loading the runtime ELF file into memory,
 * mapping the required physical memory for the enclave, and setting up the
 * virtual-to-physical memory mappings.
 *
 * @param dummy Unused parameter.
 * @param dram_base The base address of the DRAM.
 * @param dram_size The size of the DRAM.
 * @param runtime_base The base address of the runtime ELF.
 * @param user_base The base address for user memory.
 * @param free_base The base address for free memory.
 * @param untrusted_ptr The base address of untrusted memory.
 * @param untrusted_size The size of untrusted memory.
 * @return 0 on success, non-zero on failure.
 */
int load_runtime(uintptr_t dummy,
                uintptr_t dram_base, uintptr_t dram_size, 
                uintptr_t runtime_base, uintptr_t user_base, 
                uintptr_t free_base, uintptr_t untrusted_ptr, 
                uintptr_t untrusted_size) {
  int ret = 0;

  root_page_table = root_page_table_storage;

  // initialize freemem
  spa_init(free_base, dram_base + dram_size - free_base);

  // validate runtime elf 
  size_t runtime_size = user_base - runtime_base;
  if (((void*) runtime_base == NULL) || (runtime_size <= 0)) {
    return -1; 
  }

  // create runtime elf struct
  elf_t runtime_elf;
  ret = elf_newFile((void*) runtime_base, runtime_size, &runtime_elf);
  if (ret != 0) {
    return ret;
  }

  // map runtime memory
  ret = loadElf(&runtime_elf, 0);
  if (ret != 0) {
    return ret;
  }

  // map enclave physical memory, so that runtime will be able to access all memory
  map_physical_memory(dram_base, dram_size);

  // map untrusted memory
  ret = map_untrusted_memory(untrusted_ptr, untrusted_size);
  if (ret != 0) {
    return ret;
  }

  free_base_final = dram_base + dram_size - spa_available() * RISCV_PAGE_SIZE;

  return ret;
}

/**
 * @brief Handles fatal error and exits the enclave.
 *
 * This function prints a fatal error message and invokes the exit system call
 * to terminate the enclave execution.
 */
void error_and_exit() {
  printf("[loader] FATAL: failed to load.\n");
  sbi_exit_enclave(-1);
}

