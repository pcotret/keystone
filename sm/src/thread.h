/**
 * @file thread.h
 * @brief Thread management and context switching for enclaves.
 */
//******************************************************************************
// Copyright (c) 2018, The Regents of the University of California (Regents).
// All Rights Reserved. See LICENSE for license details.
//------------------------------------------------------------------------------
#ifndef __THREAD_H__
#define __THREAD_H__

#include <sbi/sbi_types.h>
#include <sbi/sbi_trap.h>
/**
 * @struct ctx
 * @brief Thread context.
 *
 * This structure defines the context of a thread, including general-purpose
 * registers and the return address (RA) and stack pointer (SP).
 */
struct ctx
{
  uintptr_t slot; /**< Thread or context slot identifier. */
  uintptr_t ra;   /**< Return address register. */
  uintptr_t sp;   /**< Stack pointer. */
  uintptr_t gp;   /**< Global pointer. */
  uintptr_t tp;   /**< Thread pointer. */
  uintptr_t t0;   /**< Temporary register. */
  uintptr_t t1;   /**< Temporary register. */
  uintptr_t t2;   /**< Temporary register. */
  uintptr_t s0;   /**< Saved register. */
  uintptr_t s1;   /**< Saved register. */
  uintptr_t a0;   /**< Argument register. */
  uintptr_t a1;   /**< Argument register. */
  uintptr_t a2;   /**< Argument register. */
  uintptr_t a3;   /**< Argument register. */
  uintptr_t a4;   /**< Argument register. */
  uintptr_t a5;   /**< Argument register. */
  uintptr_t a6;   /**< Argument register. */
  uintptr_t a7;   /**< Argument register. */
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
  uintptr_t t3;   /**< Temporary register. */
  uintptr_t t4;   /**< Temporary register. */
  uintptr_t t5;   /**< Temporary register. */
  uintptr_t t6;   /**< Temporary register. */
} __packed;

/**
 * @struct csrs
 * @brief Supervisor Control and Status Registers (CSRs).
 *
 * This structure contains the CSR registers specific to supervisor mode,
 * including status, exception handling, and memory protection configuration.
 */
struct csrs
{
  uintptr_t sstatus;    /**< Supervisor status register. */
  uintptr_t sedeleg;    /**< Supervisor exception delegation register. */
  uintptr_t sideleg;    /**< Supervisor interrupt delegation register. */
  uintptr_t sie;        /**< Supervisor interrupt-enable register. */
  uintptr_t stvec;      /**< Supervisor trap handler base address. */
  uintptr_t scounteren; /**< Supervisor counter enable. */

  /*  Supervisor Trap Handling */
  uintptr_t sscratch;   /**< Scratch register for supervisor trap handlers. */
  uintptr_t sepc;       /**< Supervisor exception program counter. */
  uintptr_t scause;     /**< Supervisor trap cause. */
  //NOTE: This should be stval, toolchain issue?
  uintptr_t sbadaddr;   /**< Supervisor bad address. */
  uintptr_t sip;        /**< Supervisor interrupt pending. */

  /*  Supervisor Protection and Translation */
  uintptr_t satp;     /**< Page-table base register. */

};

/* enclave thread state */
/**
 * @struct thread_state
 * @brief Enclave thread state.
 *
 * This structure represents the state of a thread in an enclave, including
 * previous mode and context state.
 */
struct thread_state
{
  int prev_mpp;           /**< Previous machine mode privilege. */
  uintptr_t prev_mepc;    /**< Previous machine exception program counter. */
  uintptr_t prev_mstatus; /**< Previous machine status register. */
  struct csrs prev_csrs;  /**< Previous CSR registers. */
  struct ctx prev_state;  /**< Previous thread context. */
};

/* swap previous and current thread states */
/**
 * @brief Swap the previous and current thread states.
 *
 * This function saves the current thread's state and restores the previous
 * thread's state. It also manages the return on resume behavior.
 *
 * @param state Pointer to the thread state structure.
 * @param regs Pointer to the trap register structure.
 * @param return_on_resume Boolean flag indicating if the thread should return
 *                         on resume.
 */
void swap_prev_state(struct thread_state* state, struct sbi_trap_regs* regs, int return_on_resume);
/**
 * @brief Swap the previous machine exception program counter (mepc).
 *
 * This function swaps the previous value of mepc (machine exception program counter).
 *
 * @param state Pointer to the thread state structure.
 * @param regs Pointer to the trap register structure.
 * @param mepc The new machine exception program counter to set.
 */
void swap_prev_mepc(struct thread_state* state, struct sbi_trap_regs* regs, uintptr_t mepc);

/**
 * @brief Swap the previous machine status register (mstatus).
 *
 * This function swaps the previous value of mstatus (machine status register).
 *
 * @param state Pointer to the thread state structure.
 * @param regs Pointer to the trap register structure.
 * @param mstatus The new machine status register to set.
 */
void swap_prev_mstatus(struct thread_state* state, struct sbi_trap_regs* regs, uintptr_t mstatus);
/**
 * @brief Swap the previous supervisor mode control and status registers (CSRs).
 *
 * This function swaps the previous values of supervisor mode CSRs.
 *
 * @param thread Pointer to the thread state structure.
 */
void swap_prev_smode_csrs(struct thread_state* thread);
/**
 * @brief Switch to the enclave's trap vector.
 *
 * This function sets the trap vector to the enclave-specific vector for handling
 * traps in enclave mode.
 */
void switch_vector_enclave(void);
/**
 * @brief Switch to the host's trap vector.
 *
 * This function sets the trap vector to the host-specific vector for handling
 * traps in host mode.
 */
void switch_vector_host(void);
/**
 * @brief Enclave-specific trap handler.
 *
 * This function handles traps within the enclave.
 */
extern void trap_vector_enclave(void);
/**
 * @brief General trap handler.
 *
 * This function handles general traps.
 */
extern void _trap_handler(void);

/* Clean state generation */
/**
 * @brief Clean the state of the thread.
 *
 * This function resets the state of the thread to a clean state.
 *
 * @param state Pointer to the thread state structure.
 */
void clean_state(struct thread_state* state);
/**
 * @brief Clean the supervisor mode control and status registers (CSRs).
 *
 * This function resets the supervisor mode CSRs to a clean state.
 *
 * @param state Pointer to the thread state structure.
 */
void clean_smode_csrs(struct thread_state* state);
#endif /* thread */
