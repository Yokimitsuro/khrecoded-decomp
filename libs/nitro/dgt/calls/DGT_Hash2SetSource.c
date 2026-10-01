typedef struct DGTHash2Context {
    unsigned int state[5];
    unsigned char buffer[64];
    unsigned int bufferedBytes;
    unsigned int blockCountLow;
    unsigned int blockCountHigh;
} DGTHash2Context;

typedef void (*DGTHash2ProcessBlock)(DGTHash2Context *context);

extern DGTHash2ProcessBlock data_02055c40;
extern void MI_CpuCopy8(const void *source, void *destination, unsigned int size);

void DGT_Hash2SetSource(
    DGTHash2Context *context,
    const void *source,
    unsigned int length)
{
    const unsigned char *input = source;
    unsigned int copyLength;

    if (length == 0) {
        return;
    }
    do {
        copyLength = 64 - context->bufferedBytes;
        if (copyLength > length) {
            copyLength = length;
        }
        MI_CpuCopy8(
            input,
            context->buffer + context->bufferedBytes,
            copyLength);
        input += copyLength;
        context->bufferedBytes += copyLength;
        length -= copyLength;
        if (context->bufferedBytes >= 64) {
            data_02055c40(context);
            context->bufferedBytes = 0;
            context->blockCountLow++;
            if (context->blockCountLow == 0) {
                context->blockCountHigh++;
            }
        }
    } while (length != 0);
}
