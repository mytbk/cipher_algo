/* SMS4 cipher algorithm:
   block: 128 bits
   key: 128 bits
   round key: 32 bits
   number of rounds: 32

   implement and test according to document and reference
   implementation
*/

typedef unsigned char UINT8;
typedef unsigned int UINT32;

static UINT8 SMS4_sbox[256] = {
  0xd6, 0x90, 0xe9, 0xfe, 0xcc, 0xe1, 0x3d, 0xb7,
  0x16, 0xb6, 0x14, 0xc2, 0x28, 0xfb, 0x2c, 0x05,
  0x2b, 0x67, 0x9a, 0x76, 0x2a, 0xbe, 0x04, 0xc3,
  0xaa, 0x44, 0x13, 0x26, 0x49, 0x86, 0x06, 0x99,
  0x9c, 0x42, 0x50, 0xf4, 0x91, 0xef, 0x98, 0x7a,
  0x33, 0x54, 0x0b, 0x43, 0xed, 0xcf, 0xac, 0x62,
  0xe4, 0xb3, 0x1c, 0xa9, 0xc9, 0x08, 0xe8, 0x95,
  0x80, 0xdf, 0x94, 0xfa, 0x75, 0x8f, 0x3f, 0xa6,
  0x47, 0x07, 0xa7, 0xfc, 0xf3, 0x73, 0x17, 0xba,
  0x83, 0x59, 0x3c, 0x19, 0xe6, 0x85, 0x4f, 0xa8,
  0x68, 0x6b, 0x81, 0xb2, 0x71, 0x64, 0xda, 0x8b,
  0xf8, 0xeb, 0x0f, 0x4b, 0x70, 0x56, 0x9d, 0x35,
  0x1e, 0x24, 0x0e, 0x5e, 0x63, 0x58, 0xd1, 0xa2,
  0x25, 0x22, 0x7c, 0x3b, 0x01, 0x21, 0x78, 0x87,
  0xd4, 0x00, 0x46, 0x57, 0x9f, 0xd3, 0x27, 0x52,
  0x4c, 0x36, 0x02, 0xe7, 0xa0, 0xc4, 0xc8, 0x9e,
  0xea, 0xbf, 0x8a, 0xd2, 0x40, 0xc7, 0x38, 0xb5,
  0xa3, 0xf7, 0xf2, 0xce, 0xf9, 0x61, 0x15, 0xa1,
  0xe0, 0xae, 0x5d, 0xa4, 0x9b, 0x34, 0x1a, 0x55,
  0xad, 0x93, 0x32, 0x30, 0xf5, 0x8c, 0xb1, 0xe3,
  0x1d, 0xf6, 0xe2, 0x2e, 0x82, 0x66, 0xca, 0x60,
  0xc0, 0x29, 0x23, 0xab, 0x0d, 0x53, 0x4e, 0x6f,
  0xd5, 0xdb, 0x37, 0x45, 0xde, 0xfd, 0x8e, 0x2f,
  0x03, 0xff, 0x6a, 0x72, 0x6d, 0x6c, 0x5b, 0x51,
  0x8d, 0x1b, 0xaf, 0x92, 0xbb, 0xdd, 0xbc, 0x7f,
  0x11, 0xd9, 0x5c, 0x41, 0x1f, 0x10, 0x5a, 0xd8,
  0x0a, 0xc1, 0x31, 0x88, 0xa5, 0xcd, 0x7b, 0xbd,
  0x2d, 0x74, 0xd0, 0x12, 0xb8, 0xe5, 0xb4, 0xb0,
  0x89, 0x69, 0x97, 0x4a, 0x0c, 0x96, 0x77, 0x7e,
  0x65, 0xb9, 0xf1, 0x09, 0xc5, 0x6e, 0xc6, 0x84,
  0x18, 0xf0, 0x7d, 0xec, 0x3a, 0xdc, 0x4d, 0x20,
  0x79, 0xee, 0x5f, 0x3e, 0xd7, 0xcb, 0x39, 0x48
};

static inline UINT32
rol32(UINT32 x, int b)
{
  return (x<<b)|(x>>(32-b));
}

static inline UINT32
SMS4_sbox_sub(UINT32 x)
{
  UINT32 t1 = SMS4_sbox[x&0xff];
  UINT32 t2 = SMS4_sbox[(x>>8)&0xff];
  UINT32 t3 = SMS4_sbox[(x>>16)&0xff];
  UINT32 t4 = SMS4_sbox[(x>>24)&0xff];
  UINT32 t = t1 | (t2<<8) | (t3<<16) | (t4<<24);
  return t;
}

static UINT32
SMS4_compound_substitute(UINT32 x)
{
  // first do substitute
  UINT32 t = SMS4_sbox_sub(x);

  // then a linear transform
  UINT32 c = t^rol32(t,2)^rol32(t,10)^rol32(t,18)^rol32(t,24);
  return c;
}

static UINT32
SMS4_round(UINT32 *input, UINT32 key)
{
  UINT32 x0 = input[0];
  UINT32 t = input[1]^input[2]^input[3]^key;
  return x0^SMS4_compound_substitute(t);
}

static UINT32
SMS4_key_transform(UINT32 x)
{
  UINT32 t = SMS4_sbox_sub(x);
  return t^rol32(t,13)^rol32(t,23);
}

UINT32
CK(UINT32 i)
{
  UINT32 t3 = (i*4+3)*7;
  t3 <<= 24;
  UINT32 t2 = t3-0x07000000;
  UINT32 t1 = t3-0x0e000000;
  UINT32 t0 = t3-0x15000000;
  return t3|(t2>>8)|(t1>>16)|(t0>>24);
}

void
SMS4_key_expansion(UINT32 *key, UINT32 *roundkeys)
{
  // use a 128-bit key to generate 32 32-bit roundkeys
  UINT32 K[36];
  static UINT32 FK[4] = {
    0xA3B1BAC6,
    0x56AA3350,
    0x677D9197,
    0xB27022DC
  };
  /*
  static UINT32 CK[32] = {
    0x150e0700, 0x312a231c, 0x4d463f38, 0x69625b54,
    0x857e7770, 0xa19a938c, 0xbdb6afa8, 0xd9d2cbc4,
    0xf5eee7e0, 0x110a03fc, 0x2d261f18, 0x49423b34,
    0x655e5750, 0x817a736c, 0x9d968f88, 0xb9b2aba4,
    0xd5cec7c0, 0xf1eae3dc, 0x0d06fff8, 0x29221b14,
    0x453e3730, 0x615a534c, 0x7d766f68, 0x99928b84,
    0xb5aea7a0, 0xd1cac3bc, 0xede6dfd8, 0x0902fbf4,
    0x251e1710, 0x413a332c, 0x5d564f48, 0x79726b64
  };
  */
  static UINT32 CK[32] =
    {
      0x00070e15,0x1c232a31,0x383f464d,0x545b6269,
      0x70777e85,0x8c939aa1,0xa8afb6bd,0xc4cbd2d9,
      0xe0e7eef5,0xfc030a11,0x181f262d,0x343b4249,
      0x50575e65,0x6c737a81,0x888f969d,0xa4abb2b9,
      0xc0c7ced5,0xdce3eaf1,0xf8ff060d,0x141b2229,
      0x30373e45,0x4c535a61,0x686f767d,0x848b9299,
      0xa0a7aeb5,0xbcc3cad1,0xd8dfe6ed,0xf4fb0209,
      0x10171e25,0x2c333a41,0x484f565d,0x646b7279
    };

  K[0] = key[0]^FK[0];
  K[1] = key[1]^FK[1];
  K[2] = key[2]^FK[2];
  K[3] = key[3]^FK[3];

  for (int i=0; i<32; i++) {
    K[i+4] = K[i]^SMS4_key_transform(K[i+1]^K[i+2]^K[i+3]^CK[i]);
    roundkeys[i] = K[i+4];
  }
}

void
SMS4_cipher(UINT32 *plain, UINT32 *key, UINT32 *cipher)
{
  UINT32 roundkeys[32];
  UINT32 X[36];

  SMS4_key_expansion(key, roundkeys);
  X[0] = plain[0];
  X[1] = plain[1];
  X[2] = plain[2];
  X[3] = plain[3];

  for (int i=0; i<32; i++) {
    X[i+4] = SMS4_round(X+i, roundkeys[i]);
  }

  cipher[0] = X[35];
  cipher[1] = X[34];
  cipher[2] = X[33];
  cipher[3] = X[32];
}