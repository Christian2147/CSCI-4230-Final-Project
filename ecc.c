#include <stdio.h>
#include <stdint.h>
#include "ecc.h"

static ECC_Int ecc_zero(void) {
    ECC_Int result = {{0, 0, 0, 0}};

    return result;
}

static ECC_Int ecc_one(void) {
    ECC_Int result = {{1, 0, 0, 0}};

    return result;
}

static ECC_Int ecc_int_add(const ECC_Int *a, const ECC_Int *b) {
    ECC_Int result = ecc_zero();

    uint64_t carry = 0;

    for (int i = 0; i < ECC_LIMBS; i++) {
        uint64_t sum = a->limb[i] + b->limb[i];
        uint64_t carry1 = 0;

        if (sum < a->limb[i]) {
            carry1 = 1;
        }

        uint64_t sum_with_carry = sum + carry;
        uint64_t carry2 = 0;

        if (sum_with_carry < sum) {
            carry2 = 1;
        }

        result.limb[i] = sum_with_carry;

        if (carry1 == 1 || carry2 == 1) {
            carry = 1;
        }
    }

    return result;
}

static ECC_Int ecc_int_sub(const ECC_Int *a, const ECC_Int *b) {
    ECC_Int result = ecc_zero();

    uint64_t borrow = 0;

    for (int i = 0; i < ECC_LIMBS; i++) {
        uint64_t difference = a->limb[i] - b->limb[i];
        uint64_t borrow1 = 0;

        if (a->limb[i] < b->limb[i]) {
            borrow1 = 1;
        }

        uint64_t difference_with_borrow = difference - borrow;
        uint64_t borrow2 = 0;

        if (difference < borrow) {
            borrow2 = 1;
        }

        result.limb[i] = difference_with_borrow;

        if (borrow1 == 1 || borrow2 == 1) {
            borrow = 1;
        }
    }

    return result;
}

static int ecc_int_get_bit(const ECC_Int *value, int bit) {
    int limb_index = bit / 64;
    int bit_index = bit % 64;

    uint64_t limb = value->limb[limb_index];
    uint64_t shifted = limb >> bit_index;
    uint64_t bit_value = shifted & 1;

    return (int)bit_value;
}

static ECC_Point ecc_point_infinity(void) {
    ECC_Point result;

    result.x = ecc_zero();
    result.y = ecc_zero();
    result.infinity = 1;

    return result;
}

int ecc_int_compare(const ECC_Int *a, const ECC_Int *b) {
    for (int i = ECC_LIMBS - 1; i >= 0; i--) {
        if (a->limb[i] > b->limb[i]) {
            return 1;
        }

        if (a->limb[i] < b->limb[i]) {
            return -1;
        }
    }

    return 0;
}

int ecc_int_is_zero(const ECC_Int *value) {
    for (int i = 0; i < ECC_LIMBS; i++) {
        if (value->limb[i] != 0) {
            return 0;
        }
    }

    return 1;
}

// Convert 32 byte big endian value to ECC int
// bytes[0] = most significant
// bytes[1] = least significant
ECC_Int ecc_int_from_bytes(const uint8_t bytes[32]) {
    ECC_Int result = ecc_zero();

    for (int i = 0; i < 32; i++) {
        int limb_index = 3 - (i / 8);
        int byte_index = i % 8;

        uint64_t byte_value = (uint64_t)bytes[i];
        int shift_amount = byte_index * 8;
        uint64_t shifted_byte = byte_value << shift_amount;

        if (shifted_byte != 0) {
            result.limb[limb_index] = result.limb[limb_index] + shifted_byte;
        }
    }
}



