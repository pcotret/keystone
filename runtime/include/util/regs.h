/**
 * @file regs.h
 * 
 * @brief Defines structures for storing register state and context information
 * 
 * This header file defines two structures:
 * - `regs`: A structure that stores the state of the registers for a specific execution context.
 * - `encl_ctx`: A structure that extends `regs` to include additional supervisor-specific control and status registers (CSRs).
 */
//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------

#ifndef _REGS_H_
#define _REGS_H_
#include <stdint.h>

/**
 * @struct regs
 * @brief Structure that holds the register values for a RISC-V execution context.
 * 
 * This structure represents the general-purpose registers for the RISC-V architecture, as well as special registers
 * like the `sepc` (Supervisor Exception Program Counter), which is used to store the program counter at the time of
 * an exception.
 */
struct regs {
	uintptr_t sepc; /**< Supervisor Exception Program Counter (SEPC) */
	uintptr_t ra;   /**< Return address register */
	uintptr_t sp;   /**< Stack pointer */
	uintptr_t gp;   /**< Global pointer */
	uintptr_t tp;   /**< Thread pointer */
	uintptr_t t0;   /**< Temporary register */
	uintptr_t t1;   /**< Temporary register */
	uintptr_t t2;   /**< Temporary register */
	uintptr_t s0;   /**< Saved register */
	uintptr_t s1;   /**< Saved register */
	uintptr_t a0;   /**< Argument registers */
	uintptr_t a1;   /**< Argument registers */
	uintptr_t a2;   /**< Argument registers */
	uintptr_t a3;   /**< Argument registers */
	uintptr_t a4;   /**< Argument registers */
	uintptr_t a5;   /**< Argument registers */
	uintptr_t a6;   /**< Argument registers */
	uintptr_t a7;   /**< Argument registers */
	uintptr_t s2;   /**< Saved register */
	uintptr_t s3;   /**< Saved register */
	uintptr_t s4;   /**< Saved register */
	uintptr_t s5;   /**< Saved register */
	uintptr_t s6;   /**< Saved register */
	uintptr_t s7;   /**< Saved register */
	uintptr_t s8;   /**< Saved register */
	uintptr_t s9;   /**< Saved register */
	uintptr_t s10;  /**< Saved register */
	uintptr_t s11;  /**< Saved register */
	uintptr_t t3;   /**< Temporary register */
	uintptr_t t4;   /**< Temporary register */
	uintptr_t t5;   /**< Temporary register */
	uintptr_t t6;   /**< Temporary register */
};

/**
 * @struct encl_ctx
 * @brief Structure that extends the register state to include supervisor-specific control and status registers (CSRs).
 * 
 * This structure extends the `regs` structure with additional registers used for managing supervisor-level context
 * and exceptions in a RISC-V system.
 */
struct encl_ctx {
	struct regs regs;   /**< General-purpose and standard registers. */
  /* Supervisor CSRs */
	uintptr_t sstatus;  /**< Supervisor status register (sstatus). */
	uintptr_t sbadaddr; /**< Bad address register (deprecated; typically use stval). */
	uintptr_t scause;   /**< Exception cause register (scause). */
};
#endif /* _REGS_H_ */
