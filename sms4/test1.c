#include <stdio.h>
#include "sms4.h"

#define TEXT {0x01234567, 0x89abcdef, 0xfedcba98, 0x76543210}

int main()
{
  UINT32 key[4] = TEXT;
  UINT32 plain[4] = TEXT;
  UINT32 roundkeys[32];
  UINT32 cipher[4];

  SMS4_key_expansion(key, roundkeys);

  for (int i=0; i<32; i++) {
    printf("0x%08x\n", roundkeys[i]);
  }

  SMS4_cipher(plain, key, cipher);

  for (int i=0; i<16; i++) {
    printf("0x%02hhx ", ((char*)cipher)[i]);
  }
  puts("");

  return 0;
}
