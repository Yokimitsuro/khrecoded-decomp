typedef unsigned char u8;
typedef unsigned long u32;

#define ENC_VAL_1 0x1000
#define ADDR_PLUS_ADDEND(ref, addend) ((u32)(&ref + ((addend) / sizeof(ref))))

#define PRIME_TRUE 251
#define PRIME_FALSE 241
#define PRIME_INTEGRITY 181

extern u32 RunEncrypted_MACOwner_IsBad(void);
extern u32 RunEncrypted_MACOwner_IsGood(void);
extern u32 RunEncrypted_ROMTest_IsBad(void);
extern u32 RunEncrypted_ROMTest_IsGood(void);

static inline u32 checkDecryptionWrapper(u8 *addr, u32 match_ret, u32 mismatch_ret) {
    u32 offset;

    addr += ENC_VAL_1;
    offset = 0;

    if (addr[offset++] != 0x0f) return mismatch_ret;
    if (addr[offset++] != 0xc0) return mismatch_ret;
    if (addr[offset++] != 0x8f) return mismatch_ret;
    if (addr[offset++] != 0xe1) return mismatch_ret;

    if (addr[offset++] != 0x0c) return mismatch_ret;
    if (addr[offset++] != 0xc0) return mismatch_ret;
    if (addr[offset++] != 0x1c) return mismatch_ret;
    if (addr[offset++] != 0xe0) return mismatch_ret;

    if (addr[offset++] != 0x00) return mismatch_ret;
    if (addr[offset++] != 0xc0) return mismatch_ret;
    if (addr[offset++] != 0xa0) return mismatch_ret;
    if (addr[offset++] != 0x03) return mismatch_ret;

    if (addr[offset++] != 0x1c) return mismatch_ret;
    if (addr[offset++] != 0xc0) return mismatch_ret;
    if (addr[offset++] != 0x8c) return mismatch_ret;
    if (addr[offset++] != 0x12) return mismatch_ret;

    return match_ret;
}
