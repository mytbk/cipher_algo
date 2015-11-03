#ifndef SMS4_H
#define SMS4_H

typedef unsigned int UINT32;
void SMS4_key_expansion(UINT32 *key, UINT32 *roundkeys);
void SMS4_cipher(UINT32 *plain, UINT32 *key, UINT32 *cipher);

#endif
