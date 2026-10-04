typedef struct DGTHash2Context {
    unsigned int state[5];
    unsigned char buffer[64];
    unsigned int bufferedBytes;
    unsigned int blockCountLow;
    unsigned int blockCountHigh;
} DGTHash2Context;

typedef void (*DGTHash2ProcessBlock)(DGTHash2Context *context);

extern DGTHash2ProcessBlock MATHi_SHA1ProcessMessageBlockFunc;
extern void MI_CpuFill8(void *destination, unsigned int value, unsigned int size);

void DGTi_Hash2FillSource(
    DGTHash2Context *context,
    unsigned int value,
    unsigned int length)
{
    unsigned int fillLength;

    if (length == 0) {
        return;
    }
    do {
        fillLength = 64 - context->bufferedBytes;
        if (fillLength > length) {
            fillLength = length;
        }
        MI_CpuFill8(
            context->buffer + context->bufferedBytes,
            value,
            fillLength);
        context->bufferedBytes += fillLength;
        length -= fillLength;
        if (context->bufferedBytes >= 64) {
            MATHi_SHA1ProcessMessageBlockFunc(context);
            context->bufferedBytes = 0;
            context->blockCountLow++;
            if (context->blockCountLow == 0) {
                context->blockCountHigh++;
            }
        }
    } while (length != 0);
}
