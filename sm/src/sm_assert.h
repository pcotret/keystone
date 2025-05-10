/**
 * @file sm_assert.h
 * @brief Assertion macro for Keystone SM with platform-specific failure handling.
 */
#ifndef __SM_ASSERT_H__

#include <sbi/sbi_console.h>
#include <sbi/sbi_hart.h>

/**
 * @def sm_assert(cond)
 * @brief Halts the system if the condition fails.
 *
 * Prints an assertion failure message and hangs the hart if @p cond is false.
 *
 * @param cond Condition to evaluate.
 */
#define sm_assert(cond) { \
  if (!(cond)) { \
    sbi_printf("[SM] assertion_failed\r\n"); \
    sbi_hart_hang(); \
  } \
}

#endif
