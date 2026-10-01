typedef unsigned char u8;
typedef unsigned int u32;

typedef struct DGTHash2Context {
    u32 state[5];
    u8 buffer[64];
    u32 bufferedBytes;
    u32 blockCountLow;
    u32 blockCountHigh;
} DGTHash2Context;

extern void DGT_Hash2SetSource(DGTHash2Context *context, const void *source, u32 length);
extern void DGTi_Hash2FillSource(DGTHash2Context *context, u8 value, u32 length);
extern void MI_CpuCopy8(const void *source, void *destination, u32 size);
extern const u8 data_02052af4[1];
extern const u8 data_02052af5[8];

static inline u32 SwapBytes32(u32 value)
{
    return ((value >> 24) & 0x000000ff) |
           ((value >> 8) & 0x0000ff00) |
           ((value << 8) & 0x00ff0000) |
           ((value << 24) & 0xff000000);
}

void DGT_Hash2GetDigest(DGTHash2Context *context, void *digest)
{
    u32 footer[2];

    footer[1] = SwapBytes32((context->blockCountLow << 9) +
                            (context->bufferedBytes << 3));
    footer[0] = SwapBytes32((context->blockCountHigh << 9) +
                            (context->blockCountLow >> 23));

    DGT_Hash2SetSource(context, data_02052af4, 1);

    if (64 - context->bufferedBytes < sizeof(footer)) {
        DGT_Hash2SetSource(context, data_02052af5, 64 - context->bufferedBytes);
    }

    DGTi_Hash2FillSource(context, 0, 56 - context->bufferedBytes);
    DGT_Hash2SetSource(context, footer, sizeof(footer));

    context->state[0] = SwapBytes32(context->state[0]);
    context->state[1] = SwapBytes32(context->state[1]);
    context->state[2] = SwapBytes32(context->state[2]);
    context->state[3] = SwapBytes32(context->state[3]);
    context->state[4] = SwapBytes32(context->state[4]);
    MI_CpuCopy8(context->state, digest, sizeof(context->state));
}