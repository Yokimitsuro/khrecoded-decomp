typedef unsigned char u8;
typedef unsigned int u32;
typedef struct MATHSHA1Context { u32 data[0x60 / 4]; } MATHSHA1Context;
typedef struct MATHiHMACFuncs {
    u32 dlength;
    u32 blength;
    void *context;
    void *hash_buf;
    void (*HashReset)(void *context);
    void (*HashSetSource)(void *context, const void *input, u32 length);
    void (*HashGetDigest)(void *context, void *digest);
} MATHiHMACFuncs;
extern const MATHiHMACFuncs data_02052b00;
extern void DGT_Hash2Reset(void *context);
extern void DGT_Hash2SetSource(void *context, const void *input, u32 length);
extern void DGT_Hash2GetDigest(void *context, void *digest);
extern void MATHi_CalcHMAC(void *digest, const void *bin, u32 binLen, const void *key, u32 keyLen, MATHiHMACFuncs *funcs);
void MATH_CalcHMACSHA1(void *digest, const void *bin, u32 binLen, const void *key, u32 keyLen)
{
    MATHSHA1Context context;
    u8 hashBuf[20];
    MATHiHMACFuncs funcs = data_02052b00;
    funcs.context = &context;
    funcs.hash_buf = hashBuf;
    funcs.HashReset = DGT_Hash2Reset;
    funcs.HashSetSource = DGT_Hash2SetSource;
    funcs.HashGetDigest = DGT_Hash2GetDigest;
    MATHi_CalcHMAC(digest, bin, binLen, key, keyLen, &funcs);
}