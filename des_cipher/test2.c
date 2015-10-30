#include <stdio.h>
#include "des.h"

static int rotatebits[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

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

int main()
{
  UINT64 plain, key, o;
  plain = 0x2064a8ecce8a4602;
  key = 0x59e8d947c971150f;

  UINT64 roundkey[16];
  roundkey[0] = rotkey(PC1(key),1);
  for (int i=1; i<16; i++) {
    roundkey[i] = rotkey(roundkey[i-1],rotatebits[i]);
  }
  for (int i=0; i<16; i++) {
    roundkey[i] = PC2(roundkey[i]);
  }

  for (int i=0; i<16; i++) {
    printf("%llx\n", roundkey[i]);
  }

  o = DES_encrypt(plain, key);
  for (int i=0; i<8; i++) {
    printf("%hhx ", o>>(i*8));
  }
  puts("");
  return 0;
}
