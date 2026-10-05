typedef unsigned int u32;

typedef struct NNSG3dGeBuffer_ {
    u32 idx;
    u32 data[192];
} NNSG3dGeBuffer;

extern NNSG3dGeBuffer *data_027e00a8;
extern volatile int data_027e00ac;

extern void MIi_CpuCopyFast(const void *source, void *destination, u32 size);
extern void MIi_CpuSend32(const void *source, volatile void *destination, u32 size);

void NNS_G3dGeBufferOP_N(u32 op, const u32 *args, u32 numWords)
{
    NNSG3dGeBuffer *buffer = data_027e00a8;
    int busy = data_027e00ac;
    u32 index = buffer->idx;

    if (busy != 0) {
        if (index + 1 + numWords <= 192) {
            buffer->data[index++] = op;
            if (numWords > 0) {
                MIi_CpuCopyFast(
                    args,
                    &data_027e00a8->data[index],
                    numWords << 2);
                index += numWords;
            }
            data_027e00a8->idx = index;
            return;
        }
        while (data_027e00ac != 0) {
        }
    }

    if (index != 0) {
        MIi_CpuSend32(
            &buffer->data[0],
            (volatile void *)0x04000400,
            index << 2);
        data_027e00a8->idx = 0;
    }

    *(volatile u32 *)0x04000400 = op;
    MIi_CpuSend32(args, (volatile void *)0x04000400, numWords << 2);
}
