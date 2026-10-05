#include "nitro/types.h"

extern int data_ov039_020bea20;
extern void func_02052528(void *record, int value0, int value1, int value2, int value3);
extern void func_02052570(void *record);

void InitStreamBufferPair(int blockCount, u32 flag)
{
    int base = data_ov039_020bea20;
    int size = blockCount << 0xc;

    func_02052528((void *)(base + 0xc9d0), 0, *(int *)(base + 0xc9c8), size, flag);
    func_02052528((void *)(base + 0xc9ec), 0, *(int *)(base + 0xc9cc), size, flag);
    func_02052570((void *)(base + 0xc9d0));
    func_02052570((void *)(base + 0xc9ec));
}
