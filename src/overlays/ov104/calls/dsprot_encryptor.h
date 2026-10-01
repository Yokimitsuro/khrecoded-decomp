typedef unsigned char u8;
typedef unsigned long u32;

#define ENC_VAL_1 0x1000
#define HW_CACHE_LINE_SIZE 32
#define HW_C7_CACHE_SET_NO_SHIFT 30
#define HW_DCACHE_SIZE 0x1000
#define ROTL(x, amount) ((amount) == 0 ? (x) : (((x) << (amount)) | ((x) >> (32 - (amount)))))

extern u8 BSS[4];

extern u32 RC4_InitAndEncryptInstructions(void *key, void *dst, void *src, u32 size);
extern u32 RC4_InitAndDecryptInstructions(void *key, void *dst, void *src, u32 size);

extern void *Encryptor_DecryptFunction(u32 key, u32 func_addr, u32 size);
extern u32 Encryptor_EncryptFunction(u32 key, u32 func_addr, u32 size);

static inline void clearDataAndInstructionCache(void) {
    asm {
        mov  ip, #0
        mov  r1, #0
    @1:
        mov  r0, #0
    @2:
        orr  r2, r1, r0
        mcr  p15, 0, ip, c7, c10, 4
        mcr  p15, 0, r2, c7, c14, 2

        add  r0, r0, #HW_CACHE_LINE_SIZE
        cmp  r0, #HW_DCACHE_SIZE / 4
        blt  @2

        add  r1, r1, #1 << HW_C7_CACHE_SET_NO_SHIFT
        cmp  r1, #0
        bne  @1

        mov  r0, #0
        mcr  p15, 0, r0, c7, c5, 0

        mcr  p15, 0, ip, c7, c10, 4
    }
}

static inline void expandRC4Key(u32 seed_key, u32 size, u32 *expanded_key) {
    expanded_key[0] = ROTL(seed_key, 0) ^ size;
    expanded_key[1] = ROTL(seed_key, 8) ^ size;
    expanded_key[2] = ROTL(seed_key, 16) ^ size;
    expanded_key[3] = ROTL(seed_key, 24) ^ size;
}
