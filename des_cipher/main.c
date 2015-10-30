#include <stdio.h>
#include <string.h>
#include "des.h"

int main()
{
  UINT64 plain, key, o;
  char *passphrase = "SECURITY";
  char *plaintext = "NETWORK INFORMATION SECURITY";
  char output[100];
  char output2[100];

  key = *(UINT64*)passphrase;
  int len = strlen(plaintext)+1;
  int outputlen = (len+7)&0xfffffff8;

  for (int i=0; i<len; i+=8) {
    *(UINT64*)(output+i) = DES_encrypt(*(UINT64*)(plaintext+i), key);
  }

  puts("\nDES (CBC mode) final result:");
  for (int i=0; i<outputlen; i++) {
    printf("%02hhx ", output[i]);
  }
  puts("\n");

  // decrypt to verify
  puts("decrypt the text to verify:");
  for (int i=0; i<outputlen; i+=8) {
    *(UINT64*)(output2+i) = DES_decrypt(*(UINT64*)(output+i), key);
  }
  puts(output2);

  return 0;
}
