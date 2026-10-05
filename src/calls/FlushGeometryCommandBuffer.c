typedef unsigned long u32;

typedef struct NNSG3dGeBuffer {
    u32 idx;
    u32 data[192];
} NNSG3dGeBuffer;

extern volatile int data_027e00ac;
extern NNSG3dGeBuffer *data_027e00a8;
extern int data_01fffea0;
extern int GXi_DmaId;

extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void MIi_CpuSend32(const void *src, volatile void *dst, u32 size);
extern void MI_SendGXCommandAsyncFast(u32 dmaNo, const void *src, u32 size,
                                      void (*callback)(void *), void *arg);
extern void MI_SendGXCommandAsync(u32 dmaNo, const void *src, u32 size,
                                  void (*callback)(void *), void *arg);
extern void func_01ffa1e8(void *arg);

void FlushGeometryCommandBuffer(const void *src, u32 size)
{
    if (size < 0x100) {
        if (data_027e00ac != 0) {
            if (data_027e00a8->idx + (size >> 2) <= 192) {
                MIi_CpuCopyFast(src, &data_027e00a8->data[data_027e00a8->idx], size);
                data_027e00a8->idx += size >> 2;
                return;
            }
            while (data_027e00ac != 0) {
            }
        }

        if (data_027e00a8->idx != 0) {
            MIi_CpuSend32(&data_027e00a8->data[0], (volatile void *)0x04000400,
                          data_027e00a8->idx << 2);
            data_027e00a8->idx = 0;
        }
        MIi_CpuSend32(src, (volatile void *)0x04000400, size);
        return;
    }

    while (data_027e00ac != 0) {
    }

    if (data_027e00a8->idx != 0) {
        MIi_CpuSend32(&data_027e00a8->data[0], (volatile void *)0x04000400,
                      data_027e00a8->idx << 2);
        data_027e00a8->idx = 0;
    }

    data_027e00ac = 1;
    if (data_01fffea0 != 0) {
        MI_SendGXCommandAsyncFast((u32)GXi_DmaId, src, size, func_01ffa1e8,
                                  (void *)&data_027e00ac);
    } else {
        MI_SendGXCommandAsync((u32)GXi_DmaId, src, size, func_01ffa1e8,
                              (void *)&data_027e00ac);
    }
}
