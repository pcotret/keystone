/**
 * @file platform.h
 * @brief FU540 platform-specific enclave data and configuration.
 *
 * This file defines the platform-specific structure and configuration for enclaves
 * on the FU540 platform. It includes parameters related to cache partitioning,
 * waymask usage, and scratchpad memory.
 * 
 * The structure `platform_enclave_data` is used to hold enclave-specific information
 * regarding cache configuration and scratchpad usage:
 * - `num_ways`: Specifies the number of ways to partition the cache. A value of 0
 *   indicates no cache partitioning.
 * - `saved_mask`: A mask of cache ways to use, relevant only when `num_ways` is greater than 0.
 * - `use_scratch`: Indicates whether scratchpad memory is used by the enclave (1) or not (0).
 */
#ifndef _FU540_H_
#define _FU540_H_

#include "waymasks.h"

/**
 * @struct platform_enclave_data
 * @brief Configuration structure for enclave settings on the platform.
 *
 * This structure holds configuration information specific to the enclave's execution environment on the platform.
 * It includes parameters for cache partitioning, waymask management, and scratchpad usage.
 */
struct platform_enclave_data {
  /* 0 means don't do cache partitioning. Otherwise the number of ways
     required. */
  size_t num_ways;      /**< The number of cache ways allocated for the enclave (0 for no partitioning). */
  /* Used if there is a waymask needed (>0 num_ways)*/
  waymask_t saved_mask; /**< The waymask for cache partitioning (used when num_ways > 0). */

  /* 0 for doesn't use scratchpad, 1 for does */
  int use_scratch;      /**< Indicates whether scratchpad memory is used (1 for yes, 0 for no). */
};

#endif /* _FU540_H_ */
