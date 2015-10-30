typedef unsigned long long UINT64;
typedef unsigned int UINT32;

UINT64 init_permutation(UINT64 x);
UINT64 final_permutation(UINT64 x);
UINT64 expansion(UINT32 k);
UINT32 permutation32(UINT32 x);
UINT64 PC1(UINT64 k);
UINT64 PC2(UINT64 k);
UINT32 substitute(int id, UINT32 input);
UINT64 DES_encrypt(UINT64 plain, UINT64 key);
UINT64 DES_decrypt(UINT64 plain, UINT64 key);
