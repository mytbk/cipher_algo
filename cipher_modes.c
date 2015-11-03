#include <string.h>

typedef void(*crypt_fn_t)(const void *plain, const void *key, void *cipher);

static void
block_xor(void *o, const void *a, const void *b, size_t size)
{
  while (size--) {
    ((char*)o)[0] = ((char*)a)[0]^((char*)b)[0];
  }
}

void
encrypt_ecb(const void *plain, const void *key, void *cipher,
            size_t bs, size_t cnt, crypt_fn_t enc)
{
  for (size_t i=0; i<cnt; i++) {
    enc(plain, key, cipher);
    plain += bs;
    cipher += bs;
  }
}

void
encrypt_cbc(const void *plain, const void *key, void *cipher,
            size_t bs, size_t cnt, crypt_fn_t enc, const void *iv)
{
  char tmp[bs], in[bs];

  memcpy(tmp, iv, bs);

  for (size_t i=0; i<cnt; i++) {
    block_xor(in, plain, tmp, bs);
    enc(in, key, cipher);
    plain += bs;
    memcpy(tmp, cipher, bs);
    cipher += bs;
  }
}

/* cfb encrypt mode:
   now only supports (cipher block size)==(block size)
*/
void
encrypt_cfb(const void *plain, const void *key, void *cipher,
            size_t bs, size_t cnt, crypt_fn_t enc, const void *iv)
{
  char tmp[bs], in[bs];

  memcpy(tmp, iv, bs);

  for (size_t i=0; i<cnt; i++) {
    enc(tmp, key, in);
    block_xor(cipher, plain, in, bs);
    plain += bs;
    memcpy(tmp, cipher, bs); // feedback cipher
    cipher += bs;
  }
}

void
encrypt_ofb(const void *plain, const void *key, void *cipher,
            size_t bs, size_t cnt, crypt_fn_t enc, const void *iv)
{
  char tmp[bs], in[bs];

  memcpy(tmp, iv, bs);

  for (size_t i=0; i<cnt; i++) {
    enc(tmp, key, in);
    block_xor(cipher, plain, in, bs);
    plain += bs;
    memcpy(tmp, in, bs); // feedback encrypted vector
    cipher += bs;
  }
}

/* encrypt in ctr mode:
   assume that cipher block size >= sizeof(size_t)
*/
void
encrypt_ctr(const void *plain, const void *key, void *cipher,
            size_t bs, size_t cnt, crypt_fn_t enc, size_t counter)
{
  char tmp[bs], in[bs];

  for (size_t i=0; i<cnt; i++) {
    memset(tmp, 0, bs);
    ((size_t*)tmp)[0] = counter;
    enc(tmp, key, in); // encrypt counter
    block_xor(cipher, plain, in, bs);
    counter++;
    plain += bs;
    cipher += bs;
  }
}
