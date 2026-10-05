#include "nitro/types.h"

typedef struct {
    s8 slot;
    u8 count;
    u8 pad_02[0x92];
    void *sendBuffer;
    void *recvBuffers[4];
} ShareBuffers;

extern ShareBuffers *data_ov015_0207e964;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void MI_CpuFill8(void *dest, u8 data, u32 size);
extern void MIi_CpuCopy16(const void *src, void *dest, u32 size);
extern void func_ov015_02072ee4(int mode);

void InitShareBuffers(const void *header) {
    u16 scratch[64] = {0};
    int i;

    data_ov015_0207e964 = NNSi_FndAllocFromDefaultHeap(sizeof(ShareBuffers));
    MI_CpuFill8(data_ov015_0207e964, 0, sizeof(ShareBuffers));
    data_ov015_0207e964->slot = -1;
    data_ov015_0207e964->count = 0;
    data_ov015_0207e964->sendBuffer = NNS_FndAllocFromDefaultExpHeapEx(0x80, 0x20);
    MI_CpuFill8(data_ov015_0207e964->sendBuffer, 0, 0x80);
    for (i = 0; i < 4; i++) {
        data_ov015_0207e964->recvBuffers[i] = NNS_FndAllocFromDefaultExpHeapEx(0x80, 0x20);
        MI_CpuFill8(data_ov015_0207e964->recvBuffers[i], 0, 0x80);
    }
    MIi_CpuCopy16(header, data_ov015_0207e964->sendBuffer, 0x70);
    func_ov015_02072ee4(0);
}
