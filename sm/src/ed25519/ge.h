/**
 * @file ge.h
 * @brief Group element operations for elliptic curve cryptography on Curve25519.
 *
 * This file defines the core representations and operations for manipulating group elements
 * on the Edwards curve used in Curve25519. Group elements are represented in different coordinate
 * systems to optimize various computations.
 */
#ifndef GE_H
#define GE_H

#include "fe.h"


/*
ge means group element.

Here the group is the set of pairs (x,y) of field elements (see fe.h)
satisfying -x^2 + y^2 = 1 + d x^2y^2
where d = -121665/121666.

Representations:
  ge_p2 (projective): (X:Y:Z) satisfying x=X/Z, y=Y/Z
  ge_p3 (extended): (X:Y:Z:T) satisfying x=X/Z, y=Y/Z, XY=ZT
  ge_p1p1 (completed): ((X:Z),(Y:T)) satisfying x=X/Z, y=Y/T
  ge_precomp (Duif): (y+x,y-x,2dxy)
*/

/**
 * @struct ge_p2
 * @brief Projective coordinates representation of a group element.
 *
 * Represents (X:Y:Z) such that x = X/Z and y = Y/Z.
 */
typedef struct {
  fe X; /**< Projective X coordinate. */
  fe Y; /**< Projective Y coordinate. */
  fe Z; /**< Projective Z coordinate. */
} ge_p2;

/**
 * @struct ge_p3
 * @brief Extended coordinates representation of a group element.
 *
 * Represents (X:Y:Z:T) such that x = X/Z, y = Y/Z, and XY = ZT.
 */
typedef struct {
  fe X; /**< Extended X coordinate. */
  fe Y; /**< Extended Y coordinate. */
  fe Z; /**< Extended Z coordinate. */
  fe T; /**< Extended T coordinate. */
} ge_p3;

/**
 * @struct ge_p1p1
 * @brief Completed coordinates representation of a group element.
 *
 * Represents ((X:Z),(Y:T)) such that x = X/Z and y = Y/T.
 */
typedef struct {
  fe X; /**< X coordinate. */
  fe Y; /**< Y coordinate. */
  fe Z; /**< Z coordinate. */
  fe T; /**< T coordinate. */
} ge_p1p1;

/**
 * @struct ge_precomp
 * @brief Precomputed group element in Duif representation.
 *
 * Stores (y+x), (y−x), and 2·d·x·y to speed up fixed-base operations.
 */
typedef struct {
  fe yplusx;  /**< y + x. */
  fe yminusx; /**< y - x. */
  fe xy2d;    /**< 2 * d * x * y. */
} ge_precomp;

/**
 * @struct ge_cached
 * @brief Cached group element used for fast addition/subtraction.
 */
typedef struct {
  fe YplusX;  /**< y + x. */
  fe YminusX; /**< y - x. */
  fe Z;       /**< Z coordinate. */
  fe T2d;     /**< 2 * d * T. */
} ge_cached;


/** @brief Convert a group element to a 32-byte representation. */
void ge_p3_tobytes(unsigned char *s, const ge_p3 *h);

/** @brief Convert a group element to bytes using projective coordinates. */
void ge_tobytes(unsigned char *s, const ge_p2 *h);

/**
 * @brief Parse a group element from a 32-byte input with optional negation.
 *
 * @param h Output group element.
 * @param s 32-byte serialized input.
 * @return 0 on success, non-zero on failure.
 */
int ge_frombytes_negate_vartime(ge_p3 *h, const unsigned char *s);


/** @brief Add two group elements: r = p + q. */
void ge_add(ge_p1p1 *r, const ge_p3 *p, const ge_cached *q);

/** @brief Subtract two group elements: r = p - q. */
void ge_sub(ge_p1p1 *r, const ge_p3 *p, const ge_cached *q);
/**
 * @brief Double scalar multiplication: r = a * A + b * B.
 *
 * @param r Output group element.
 * @param a Scalar multiplier for A.
 * @param A Group element.
 * @param b Scalar multiplier for B.
 */
void ge_double_scalarmult_vartime(ge_p2 *r, const unsigned char *a, const ge_p3 *A, const unsigned char *b);

/** @brief Multiply and add: r = p + q (precomputed). */
void ge_madd(ge_p1p1 *r, const ge_p3 *p, const ge_precomp *q);

/** @brief Multiply and subtract: r = p - q (precomputed). */
void ge_msub(ge_p1p1 *r, const ge_p3 *p, const ge_precomp *q);

/** @brief Scalar multiplication with the curve base point. */
void ge_scalarmult_base(ge_p3 *h, const unsigned char *a);
/** @brief Convert completed to projective coordinates. */
void ge_p1p1_to_p2(ge_p2 *r, const ge_p1p1 *p);

/** @brief Convert completed to extended coordinates. */
void ge_p1p1_to_p3(ge_p3 *r, const ge_p1p1 *p);
/** @brief Set a projective element to zero (identity). */
void ge_p2_0(ge_p2 *h);

/** @brief Double a projective element. */
void ge_p2_dbl(ge_p1p1 *r, const ge_p2 *p);

/** @brief Set an extended element to zero (identity). */
void ge_p3_0(ge_p3 *h);
/** @brief Double an extended element. */
void ge_p3_dbl(ge_p1p1 *r, const ge_p3 *p);
/** @brief Convert extended to cached representation. */
void ge_p3_to_cached(ge_cached *r, const ge_p3 *p);
/** @brief Convert extended to projective coordinates. */
void ge_p3_to_p2(ge_p2 *r, const ge_p3 *p);

#endif
