#ifndef ECDHE_H
#define ECDHE_H

#include "ecc.h"

// Generate an ephemeral ECDHE key pair
ECC_KeyPair ecdhe_generate_keypair(const ECC_Curve *curve);

// Calculate the shared secret
int ecdhe_compute_shared_secret(
    const ECC_Curve *curve,
    const ECC_Int *private_key,
    const ECC_Point *remote_public_key,
    ECC_Int *shared_secret
);

#endif