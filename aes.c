#include <stdio.h>
#include <string.h>
#include <ctype.h>

unsigned char s[256] =
{
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

unsigned char Rcon[256] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
    0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39,
    0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a,
    0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
    0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
    0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc,
    0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,
    0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
    0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
    0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20,
    0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35,
    0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
    0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
    0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63,
    0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd,
    0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d
};

void gmix_column(unsigned char *r) {
        unsigned char a[4];
        unsigned char b[4];
        unsigned char c;
        unsigned char h;
        /* The array 'a' is simply a copy of the input array 'r'
         * The array 'b' is each element of the array 'a' multiplied by 2
         * in Rijndael's Galois field
         * a[n] ^ b[n] is element n multiplied by 3 in Rijndael's Galois field */ 
        for(c=0;c<4;c++) {
                a[c] = r[c];
                /* h is 0xff if the high bit of r[c] is set, 0 otherwise */
                h = (unsigned char)((signed char)r[c] >> 7); /* arithmetic right shift, thus shifting in either zeros or ones */
                b[c] = r[c] << 1; /* implicitly removes high bit because b[c] is an 8-bit char, so we xor by 0x1b and not 0x11b in the next line */
                b[c] ^= 0x1B & h; /* Rijndael's Galois field */
        }
        r[0] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1]; /* 2 * a0 + a3 + a2 + 3 * a1 */
        r[1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2]; /* 2 * a1 + a0 + a3 + 3 * a2 */
        r[2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3]; /* 2 * a2 + a1 + a0 + 3 * a3 */
        r[3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0]; /* 2 * a3 + a2 + a1 + 3 * a0 */
}

void expandKey(const unsigned char *in, unsigned char *out, unsigned char rcon)
{
    unsigned int w[4],k[4],g;
    int i;
    for (i=0; i<4; i++) {
        w[i] = (in[i+12]<<24) | (in[i+8]<<16) | (in[i+4]<<8) | in[i];
    }
    // w[i+4] = g(w[i+3])^w[i]
    // g(w[i+3])
    g = (s[in[3]]<<24) | (s[in[15]]<<16) | (s[in[11]]<<8) | s[in[7]];
    g ^= rcon;
    k[0] = g^w[0];
    // w[i+5] = w[i+4]^w[i+1]
    k[1] = k[0]^w[1];
    // w[i+6] = w[i+5]^w[i+2]
    k[2] = k[1]^w[2];
    // w[i+7] = w[i+6]^w[i+3]
    k[3] = k[2]^w[3];
    for (i=0; i<4; i++) {
        out[i+0] = k[i];
        out[i+4] = (k[i]>>8);
        out[i+8] = (k[i]>>16);
        out[i+12] = (k[i]>>24);
    }
}

static inline void
shiftrows(unsigned char *state)
{
    unsigned int t;
    t = *(unsigned int*)(&state[4]);
    *(unsigned int*)(&state[4]) = (t>>8)|(t<<24);
    t = *(unsigned int*)(&state[8]);
    *(unsigned int*)(&state[8]) = (t>>16)|(t<<16);
    t = *(unsigned int*)(&state[12]);
    *(unsigned int*)(&state[12]) = (t>>24)|(t<<8);
}

static inline void
aes_log(const unsigned char s[], const char *l)
{
#ifdef LOGGING
    int i;

    printf("%s: ", l);
    
    for (i=0; i<16; i++) {
        printf("%x,", s[i]);
    }
    puts("");
#endif
}

void
aes128(unsigned char *input, const unsigned char *key, unsigned char *output)
{
    unsigned char state[16];
    unsigned char tk[16];
    unsigned char roundkey[16];
    int i,r;

    memcpy(tk, key, sizeof(tk));
    
    /* initial round */
    aes_log(input, "input");
    aes_log(key, "key");
    
    for (i=0; i<16; i++) {
        state[i] = input[i]^key[i];
    }

    /* 9 rounds */
    aes_log(state, "after initial");
    
    for (r=1; r<=9; r++) {
        // sub bytes
        for (i=0; i<16; i++) {
            state[i] = s[state[i]];
        }
        aes_log(state, "after subbytes");
        // shift rows
        shiftrows(state);
        aes_log(state, "after shift rows");
        // mix columns
        for (i=0; i<4; i++) {
            unsigned char t[4];
            t[0] = state[i];
            t[1] = state[i+4];
            t[2] = state[i+8];
            t[3] = state[i+12];
            gmix_column(t);
            state[i] = t[0];
            state[i+4] = t[1];
            state[i+8] = t[2];
            state[i+12] = t[3];
        }
        aes_log(state, "after mix column");
        // add round key
        expandKey(tk, roundkey, Rcon[r]);
        memcpy(tk, roundkey, sizeof(roundkey));
        aes_log(roundkey, "roundkey");
        for (i=0; i<16; i++) {
            state[i] ^= roundkey[i];
        }
        aes_log(state, "end of round");
    }
    
    /* final round */
    for (i=0; i<16; i++) {
        state[i] = s[state[i]];
    }
    aes_log(state, "final subbytes");
    shiftrows(state);
    aes_log(state, "final shiftrows");
    expandKey(tk, roundkey, Rcon[10]);
    aes_log(roundkey, "final roundkey");
    for (i=0; i<16; i++) {
        output[i] = state[i] ^ roundkey[i];
    }
    aes_log(output, "final output");
    
}

static inline
unsigned hextoint(char c)
{
    if (isalpha(c)) {
        return (c&0x1f)+9;
    }
    if (isdigit(c)) {
        return c&0xf;
    }
    else return -1;
}

static inline
void transpose(unsigned char a[][4])
{
    unsigned int *s = (unsigned int*)a;
    unsigned int t[4];
    int i;
    for (i=0; i<4; i++) {
        t[i] = (a[0][i]) | (a[1][i]<<8) | (a[2][i]<<16) | (a[3][i]<<24);
    }
    for (i=0; i<4; i++) {
        s[i] = t[i];
    }
}

int
main(int argc, char *argv[])
{
    /* usage: aes -k <key> -i <data> -o <out> */
    int i;
    unsigned char key[16];
    
    char *keyfile, *datafile, *outfile;
    
    for (i=1; i<argc; i++) {
        if (strcmp(argv[i],"-k")==0) {
            keyfile = argv[i+1];
            i++;
        }
        else if (strcmp(argv[i],"-i")==0) {
            datafile = argv[i+1];
            i++;
        }
        else if (strcmp(argv[i], "-o")==0) {
            outfile = argv[i+1];
            i++;
        }
    }

    FILE *fKey, *fin, *fout;
    fKey = fopen(keyfile, "rb");
    for (i=0; i<16; i++) {
        char k[2];
        fread(k, 2, 1, fKey);
        key[(i%4)*4+(i/4)] = hextoint(k[0])*16+hextoint(k[1]);
    }
    fclose(fKey);
    fin = fopen(datafile, "rb");
    fout = fopen(outfile, "wb");
    while (!feof(fin)) {
        unsigned char data[16],out[16];
        if (fread(data, 16, 1, fin)==1) {
            transpose(data);
            aes128(data, key, out);
            transpose(out);
            fwrite(out, 16, 1, fout);
        }
    }
    fclose(fin);
    fclose(fout);

    return 0;
}






