typedef struct DGTHash2Context {
    unsigned int state[5];
    unsigned char buffer[64];
    unsigned int bufferedBytes;
    unsigned int lengthLow;
    unsigned int lengthHigh;
} DGTHash2Context;

void DGT_Hash2Reset(DGTHash2Context *context)
{
    context->lengthLow = 0;
    context->lengthHigh = 0;
    context->bufferedBytes = 0;
    context->state[0] = 0x67452301;
    context->state[1] = 0xefcdab89;
    context->state[2] = 0x98badcfe;
    context->state[3] = 0x10325476;
    context->state[4] = 0xc3d2e1f0;
}
