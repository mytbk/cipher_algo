#include <stdio.h>
#include "des.h"

UINT64 roundcrypt(UINT64 data, UINT64 sub)
{
  UINT32 left = data, right = data>>32;

  // function F
  UINT64 expan = expansion(right);
  UINT64 F_expan = expan^sub;
  UINT64 subs = 0;
  // do substitution
  for (int i=0; i<8; i++) {
    subs |= substitute(i, F_expan&0x3f)<<(i*4);
    F_expan >>= 6;
  }
  // permutation
  UINT32 F_result = permutation32(subs);

  UINT32 newleft = right, newright = left^F_result;
  UINT64 output = newleft | (((UINT64)newright)<<32);
  return output;
}

static int rotatebits[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

/* rotation:
   rotation shift left for each 28-bit data
   @input: 56-bit round key
   @output: 56-bit round key after rotation
*/

static UINT64
rotkey(UINT64 k, int b)
{
  UINT64 left = k&0xfffffff;
  UINT64 right = k&0xfffffff0000000;
  UINT64 newl, newr;
  newl = (left<<b)|(left>>(28-b));
  newr = (right<<b)|(right>>(28-b));
  return (newl&0xfffffff)|(newr&0xfffffff0000000);
}

UINT64 DES_encrypt(UINT64 plain, UINT64 key)
{
  UINT64 p1 = init_permutation(plain);
  UINT64 roundkey[16];
  roundkey[0] = rotkey(PC1(key),1);
  for (int i=1; i<16; i++) {
    roundkey[i] = rotkey(roundkey[i-1],rotatebits[i]);
  }
  for (int i=0; i<16; i++) {
    roundkey[i] = PC2(roundkey[i]);
  }

  for (int i=0; i<16; i++) {
#ifdef PRINT_PROCESS
    printf("round %d: text=0x%llx subkey=0x%llx\n",
           i, p1, roundkey[i]);
#endif
    p1 = roundcrypt(p1, roundkey[i]);
#ifdef PRINT_PROCESS
    printf("result=0x%llx\n", p1);
#endif
  }

  // swap
  UINT64 sw = (p1<<32)|(p1>>32);
  return final_permutation(sw);
}

UINT64 DES_decrypt(UINT64 plain, UINT64 key)
{
  UINT64 p1 = init_permutation(plain);
  UINT64 roundkey[16];
  roundkey[0] = rotkey(PC1(key),1);
  for (int i=1; i<16; i++) {
    roundkey[i] = rotkey(roundkey[i-1],rotatebits[i]);
  }
  for (int i=0; i<16; i++) {
    roundkey[i] = PC2(roundkey[i]);
  }

  for (int i=0; i<16; i++) {
    p1 = roundcrypt(p1, roundkey[15-i]);
  }

  // swap
  UINT64 sw = (p1<<32)|(p1>>32);
  return final_permutation(sw);
}
