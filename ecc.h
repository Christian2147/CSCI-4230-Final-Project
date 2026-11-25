#ifndef ECC_H
#define ECC_H

#define ECC_LIMBS 4

#include <stdint.h>

// We are using 256 bit unsigned integers
typedef struct {
    uint64_t limb[ECC_LIMBS];
} ECC_Int;

// Define elliptic curve structure
typedef struct {
    ECC_Int p;
    ECC_Int a;
    ECC_Int b;
    ECC_Int gx;
    ECC_Int gy;
    ECC_Int n;
} ECC_Curve;

// Define elliptic point structure
typedef struct {
    ECC_Int x;
    ECC_Int y;
    int infinity;
} ECC_Point;

// ECC Key-paur
typedef struct {
    ECC_Int private_key;
    ECC_Point public_key;
} ECC_KeyPair;

// ECC Integer Operations
int ecc_int_compare(const ECC_Int *a, const ECC_Int *b);
int ecc_int_is_zero(const ECC_Int *value);
ECC_Int ecc_int_from_bytes(const uint8_t bytes[32]);

// Modular Arithmatic
ECC_Int ecc_mod_add(const ECC_Int *a, const ECC_Int *b, const ECC_Int *p);
ECC_Int ecc_mod_sub(const ECC_Int *a, const ECC_Int *b, const ECC_Int *p);
ECC_Int ecc_mod_mul(const ECC_Int *a, const ECC_Int *b, const ECC_Int *p);
ECC_Int ecc_mod_inverse(const ECC_Int *a, const ECC_Int *p);

// Check if point belongs to curve
int ecc_is_on_curve(ECC_Curve *curve, ECC_Point *point);

// Add 2 points
ECC_Point ecc_point_add(ECC_Curve *curve, ECC_Point *p1, ECC_Point *p2);

// Double a point
ECC_Point ecc_point_double(ECC_Curve *curve, ECC_Point *point);

// Multiply by scaler
ECC_Point ecc_scalar_multiply(ECC_Curve *curve, const ECC_Int *scalar, ECC_Point *point);

// Key generation functions still needed
ECC_Int ecc_generate_private_key(const ECC_Int *n);
ECC_KeyPair ecc_generate_keypair(const ECC_Curve *curve);

#endif