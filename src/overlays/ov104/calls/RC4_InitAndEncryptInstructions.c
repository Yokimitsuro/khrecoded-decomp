typedef unsigned long u32;
typedef unsigned char u8;

typedef struct RC4Context {
    int x;
    int i;
    int j;
    u8 state[256];
} RC4Context;

extern void RC4_Init(RC4Context *context, const void *key, u32 keyLength);
extern u32 RC4_EncryptInstructions(RC4Context *context, void *source, void *destination, u32 size);

u32 RC4_InitAndEncryptInstructions(void *key, void *destination, void *source, u32 size)
{
    RC4Context context;
    RC4_Init(&context, key, 16);
    return RC4_EncryptInstructions(&context, destination, source, size) == -1 ? -1 : 0;
}