/**
 * @file keystone.h
 * @brief Keystone Enclave Management API
 */
//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
#ifndef _KEYSTONE_H_
#define _KEYSTONE_H_

#include <asm/sbi.h>
#include <asm/csr.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/idr.h>

#include <linux/file.h>

/* IMPORTANT: This code assumes Sv39 */
#include "riscv64.h"

/**
 * @brief Rounds an address up to the nearest page boundary.
 *
 * This macro rounds up the given address to the next multiple
 * of PAGE_SIZE, ensuring page-aligned memory.
 *
 * @param addr Address to round up.
 * @return Page-aligned address.
 */
#define PAGE_UP(addr)	(((addr)+((PAGE_SIZE)-1))&(~((PAGE_SIZE)-1)))

/**
 * @typedef vaddr_t
 * @brief Virtual address type.
 *
 * This type is used to represent virtual addresses in the Keystone
 * enclave system. It is an alias for `uintptr_t`.
 */
typedef uintptr_t vaddr_t;
/**
 * @typedef paddr_t
 * @brief Physical address type.
 *
 * This type is used to represent physical addresses in the Keystone
 * enclave system. It is an alias for `uintptr_t`.
 */
typedef uintptr_t paddr_t;
/**
 * @brief Misc device representing the Keystone enclave driver.
 *
 * Externally defined miscdevice structure used to register the Keystone
 * device with the Linux kernel's misc device framework.
 */
extern struct miscdevice keystone_dev;
/**
 * @brief IOCTL handler for the Keystone device.
 *
 * This function handles IOCTL commands for interacting with the Keystone device.
 *
 * @param filep File pointer for the Keystone device.
 * @param cmd The IOCTL command to execute.
 * @param arg Argument passed with the IOCTL command.
 * @return The result of the IOCTL command execution.
 */
long keystone_ioctl(struct file* filep, unsigned int cmd, unsigned long arg);
/**
 * @brief Release function for the Keystone device.
 *
 * This function is called when the Keystone device is released.
 *
 * @param inode The inode of the Keystone device.
 * @param file File pointer to the Keystone device.
 * @return 0 on success, or an error code.
 */
int keystone_release(struct inode *inode, struct file *file);
/**
 * @brief Memory mapping function for the Keystone device.
 *
 * This function sets up memory mapping for the Keystone device.
 *
 * @param filp File pointer for the Keystone device.
 * @param vma The virtual memory area to map.
 * @return 0 on success, or an error code.
 */
int keystone_mmap(struct file *filp, struct vm_area_struct *vma);

/* enclave private memory */
/**
 * @struct epm
 * @brief Enclave Private Memory (EPM) region descriptor.
 * 
 * Represents a private memory region allocated for the enclave. This memory
 * is isolated from other entities and managed with its own page table.
 */
struct epm {
  pte_t* root_page_table; /**< Pointer to the root of the enclave's page table. */
  vaddr_t ptr;            /**< Virtual address base of the EPM region. */
  size_t size;            /**< Size of the EPM in bytes. */
  unsigned long order;    /**< Allocation order used for page granularity (e.g., for buddy allocators). */
  paddr_t pa;             /**< Physical address of the base of the EPM. */
  bool is_cma;            /**< True if the memory was allocated using CMA (Contiguous Memory Allocator). */
};

/**
 * @struct utm
 * @brief Untrusted Memory (UTM) region descriptor.
 * 
 * Describes a memory region accessible by both enclave and non-enclave code.
 * Used for communication or data exchange between the enclave and the host.
 */
struct utm {
  pte_t* root_page_table; /**< Pointer to the page table covering the UTM region. */
  void* ptr;              /**< Pointer to the base of the UTM region. */
  size_t size;            /**< Size of the UTM in bytes. */
  unsigned long order;    /**< Allocation order used for page granularity. */
};

/**
 * @struct enclave
 * @brief Enclave metadata structure.
 * 
 * Holds metadata and memory mappings for a single enclave instance.
 */
struct enclave
{
  unsigned long eid;  /**< Enclave ID (EID), uniquely identifies the enclave. */
  int close_on_pexit; /**< Flag indicating whether to close the enclave when the parent exits. */
  struct utm* utm;    /**< Pointer to associated untrusted memory (UTM). */
  struct epm* epm;    /**< Pointer to associated private enclave memory (EPM). */
  bool is_init;       /**< True if the enclave has been successfully initialized. */
};


// global debug functions
/**
 * @brief Debugging function to dump memory contents.
 *
 * This function dumps the memory contents for debugging purposes.
 *
 * @param ptr Pointer to the memory to dump.
 * @param size Size of the memory to dump.
 */
void debug_dump(char* ptr, unsigned long size);

// runtime/app loader
/**
 * @brief Initialize runtime memory for the enclave.
 *
 * This function initializes the runtime environment for the given enclave,
 * setting up the required memory mappings.
 *
 * @param enclave The enclave to initialize the runtime for.
 * @param rt_ptr Pointer to the runtime code in user space.
 * @param rt_sz Size of the runtime code.
 * @param rt_stack_sz Size of the runtime stack.
 * @param rt_offset Offset for the runtime in memory.
 * @return 0 on success, or an error code.
 */
int keystone_rtld_init_runtime(struct enclave* enclave, void* __user rt_ptr, size_t rt_sz, unsigned long rt_stack_sz, unsigned long* rt_offset);

/**
 * @brief Initialize application memory for the enclave.
 *
 * This function initializes the application environment for the given enclave,
 * setting up the required memory mappings.
 *
 * @param enclave The enclave to initialize the application for.
 * @param app_ptr Pointer to the application code in user space.
 * @param app_sz Size of the application code.
 * @param app_stack_sz Size of the application stack.
 * @param stack_offset Offset for the application stack in memory.
 * @return 0 on success, or an error code.
 */
int keystone_rtld_init_app(struct enclave* enclave, void* __user app_ptr, size_t app_sz, size_t app_stack_sz, unsigned long stack_offset);

// untrusted memory mapper
/**
 * @brief Initialize untrusted memory for the enclave.
 *
 * This function sets up memory mappings for the untrusted memory area.
 *
 * @param enclave The enclave to initialize the untrusted memory for.
 * @param untrusted_ptr Pointer to the untrusted memory.
 * @param untrusted_size Size of the untrusted memory.
 * @return 0 on success, or an error code.
 */
int keystone_rtld_init_untrusted(struct enclave* enclave, void* untrusted_ptr, size_t untrusted_size);

/**
 * @brief Retrieve an enclave by its identifier.
 *
 * This function retrieves the enclave corresponding to the specified ID.
 *
 * @param ueid The enclave ID.
 * @return A pointer to the enclave, or NULL if not found.
 */
struct enclave* get_enclave_by_id(unsigned int ueid);
/**
 * @brief Create a new enclave.
 *
 * This function creates a new enclave with the specified number of pages.
 *
 * @param min_pages The minimum number of pages required for the enclave.
 * @return A pointer to the newly created enclave.
 */
struct enclave* create_enclave(unsigned long min_pages);
/**
 * @brief Destroy an existing enclave.
 *
 * This function destroys the specified enclave and frees associated resources.
 *
 * @param enclave The enclave to destroy.
 * @return 0 on success, or an error code.
 */
int destroy_enclave(struct enclave* enclave);
/**
 * @brief Allocate an ID for the enclave in the IDR.
 *
 * This function allocates an ID for the given enclave in the IDR.
 *
 * @param enclave The enclave to allocate an ID for.
 * @return The allocated ID.
 */
unsigned int enclave_idr_alloc(struct enclave* enclave);
/**
 * @brief Remove an enclave from the IDR by its ID.
 *
 * This function removes the specified enclave from the IDR.
 *
 * @param ueid The ID of the enclave to remove.
 * @return A pointer to the removed enclave, or NULL if not found.
 */
struct enclave* enclave_idr_remove(unsigned int ueid);
/**
 * @brief Retrieve an enclave by its identifier.
 *
 * This function retrieves the enclave corresponding to the specified ID.
 *
 * @param ueid The enclave ID.
 * @return A pointer to the enclave, or NULL if not found.
 */
struct enclave* get_enclave_by_id(unsigned int ueid);

/**
 * @brief Compute the SATP register value for the given EPM.
 *
 * This function returns the SATP (Supervisor Address Translation and Protection)
 * register value by combining the root page table address of the EPM (Enclave Page Manager)
 * with the current SATP mode (e.g., Sv39 or Sv48).
 *
 * @param epm Pointer to the enclave's page manager structure.
 * @return Encoded SATP value for the EPM's root page table.
 */
static inline uintptr_t  epm_satp(struct epm* epm) {
  return ((uintptr_t)epm->root_page_table >> RISCV_PGSHIFT | SATP_MODE_CHOICE);
}
/**
 * @brief Destroy the enclave private memory (EPM).
 *
 * This function destroys the specified EPM and frees associated resources.
 *
 * @param epm The EPM to destroy.
 * @return 0 on success, or an error code.
 */
int epm_destroy(struct epm* epm);
/**
 * @brief Initialize the enclave private memory (EPM).
 *
 * This function initializes the specified EPM with the given number of entries.
 *
 * @param epm The EPM to initialize.
 * @param count The number of entries in the EPM.
 * @return 0 on success, or an error code.
 */
int epm_init(struct epm* epm, unsigned int count);
/**
 * @brief Destroy the untrusted memory (UTM).
 *
 * This function destroys the specified UTM and frees associated resources.
 *
 * @param utm The UTM to destroy.
 * @return 0 on success, or an error code.
 */ 
int utm_destroy(struct utm* utm);
/**
 * @brief Initialize the untrusted memory (UTM).
 *
 * This function initializes the specified UTM with the given size.
 *
 * @param utm The UTM to initialize.
 * @param untrusted_size The size of the untrusted memory.
 * @return 0 on success, or an error code.
 */
int utm_init(struct utm* utm, size_t untrusted_size);
/**
 * @brief Convert a virtual address to a physical address for the EPM.
 *
 * This function converts the given virtual address to a physical address
 * for the specified EPM.
 *
 * @param epm The EPM to convert the address for.
 * @param addr The virtual address to convert.
 * @return The corresponding physical address.
 */
paddr_t epm_va_to_pa(struct epm* epm, vaddr_t addr);

/** 
 * @brief Log information related to Keystone.
 *
 * This function logs informational messages related to Keystone.
 *
 * @param fmt The format string.
 * @param ... Additional arguments for the format string.
 */
#define keystone_info(fmt, ...) \
  pr_info("keystone_enclave: " fmt, ##__VA_ARGS__)
/** 
 * @brief Log error messages related to Keystone.
 *
 * This function logs error messages related to Keystone.
 *
 * @param fmt The format string.
 * @param ... Additional arguments for the format string.
 */
#define keystone_err(fmt, ...) \
  pr_err("keystone_enclave: " fmt, ##__VA_ARGS__)
/** 
 * @brief Log warning messages related to Keystone.
 *
 * This function logs warning messages related to Keystone.
 *
 * @param fmt The format string.
 * @param ... Additional arguments for the format string.
 */
#define keystone_warn(fmt, ...) \
  pr_warn("keystone_enclave: " fmt, ##__VA_ARGS__)
#endif
