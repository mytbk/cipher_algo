#include <stdio.h>
#include "des.h"

static void
printhex(UINT64 o)
{
  for (int i=0; i<8; i++) {
    printf("%0hhx ", o>>(i*8));
  }
  puts("");
}

int main()
{
  UINT64 plain, key, o;
  plain = 0xe7cdab8967452301;
  key = 0xefcdab8967452301;

  // test init and final permutation
  printhex(plain);
  o = init_permutation(plain);
  printhex(o);
  o = final_permutation(o);
  printhex(o);
  puts("");

  o = DES_encrypt(plain, key);
  printhex(o);
  o = DES_decrypt(o, key);
  printhex(o); // should be the same as plain text
  puts("");

  return 0;
}
