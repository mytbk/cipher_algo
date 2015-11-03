#ifndef CIPHER_MODE_H
#define CIPHER_MODE_H

#include <string.h>

typedef void(*crypt_fn_t)(const void *plain, const void *key, void *cipher);

void
encrypt_ecb(const void *plain, const void *key, void *cipher,
            size_t bs, size_t cnt, crypt_fn_t enc);
void
encrypt_cbc(const void *plain, const void *key, void *cipher,
            size_t bs, size_t cnt, crypt_fn_t enc, const void *iv);
void
encrypt_cfb(const void *plain, const void *key, void *cipher,
            size_t bs, size_t cnt, crypt_fn_t enc, const void *iv);
void
encrypt_ofb(const void *plain, const void *key, void *cipher,
            size_t bs, size_t cnt, crypt_fn_t enc, const void *iv);
void
encrypt_ctr(const void *plain, const void *key, void *cipher,
            size_t bs, size_t cnt, crypt_fn_t enc, size_t counter);

#endif
