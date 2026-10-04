typedef unsigned long u32;

typedef struct DGTHash2Context {
    u32 state[5];
    u32 messageBlock[16];
    u32 bufferedBytes;
    u32 blockCountLow;
    u32 blockCountHigh;
} DGTHash2Context;

extern void MATHi_SHA1ProcessBlock(DGTHash2Context *context);

void MATHi_SHA1ProcessBlockForOverlay(DGTHash2Context *context)
{
    u32 savedWord6 = context->messageBlock[6];
    u32 savedWord14 = context->messageBlock[14];

    context->messageBlock[6] = 0;
    context->messageBlock[14] = 0;
    MATHi_SHA1ProcessBlock(context);
    context->messageBlock[6] = savedWord6;
    context->messageBlock[14] = savedWord14;
}