/**
 * @file safe_math_util.h
 * @brief Safe arithmetic utility macros using compiler built-ins for overflow detection.
 */
#ifndef _SAFE_MATH_UTIL_H_
#define _SAFE_MATH_UTIL_H_

// TODO: We may want to add checks for GCC/Clang version. We also want
// to add wrappers for other checked math functions.
/**
 * @def CHECKED_ADD(a, b, out)
 * @brief Performs unsigned addition with overflow check.
 *
 * Uses `__builtin_uadd_overflow` or `__builtin_uaddl_overflow` depending on XLEN.
 * 
 * @param a First operand.
 * @param b Second operand.
 * @param out Pointer to store the result.
 * @return Non-zero if overflow occurred, zero otherwise.
 */
#if __riscv_xlen == 32
#define CHECKED_ADD(a, b, out) (__builtin_uadd_overflow(a, b, (unsigned int*) out))
#else
#define CHECKED_ADD(a, b, out) (__builtin_uaddl_overflow(a, b, (unsigned long int*) out))
#endif

#endif /* _SAFE_MATH_UTIL_H_ */
