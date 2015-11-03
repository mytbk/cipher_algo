#include "cipher_modes.h"
#include "../aes/aes.h"

#define COMMON_PARAM const void *plain, const void *key, void *cipher, size_t size
#define COMMON_PARAM_CALL plain, key, cipher, 16, size/16, aes128_cipher

void
aes128_ecb(COMMON_PARAM)
{
  // size should be multiples of 16
  encrypt_ecb(COMMON_PARAM_CALL);
}

void
aes128_cbc(COMMON_PARAM, const void *iv)
{
  encrypt_cbc(COMMON_PARAM_CALL, iv);
}

void
aes128_cfb(COMMON_PARAM, const void *iv)
{
  encrypt_cfb(COMMON_PARAM_CALL, iv);
}

void
aes128_ofb(COMMON_PARAM, const void *iv)
{
  encrypt_ofb(COMMON_PARAM_CALL, iv);
}

void
aes128_ctr(COMMON_PARAM, size_t counter)
{
  encrypt_ctr(COMMON_PARAM_CALL, counter);
}
