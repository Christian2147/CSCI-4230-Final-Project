#ifndef ECDSA_H
#define ECDSA_H

#include "ecc.h"

ECC_KeyPair ecdsa_generate_keypair(const ECC_Curve *curve);

// Sign message hash
int ecdsa_sign(
    const ECC_Curve *curve,
    const ECC_Int *private_key,
    const ECC_Int *message_hash,
    ECC_Int *signature_r,
    ECC_Int *signature_s
);

// verify with public key
int ecdsa_verify(
    const ECC_Curve *curve,
    const ECC_Point *public_key,
    const ECC_Int *message_hash,
    const ECC_Int *signature_r,
    const ECC_Int *signature_s
);

#endif