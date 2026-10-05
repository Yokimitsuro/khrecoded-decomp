#include "nitro/types.h"

typedef struct GaugeSlot {
    u16 maximum;
    u16 current;
    u16 target;
} GaugeSlot;

typedef struct GaugeLayout {
    u32 offset;
    u32 size;
    s32 scale;
} GaugeLayout;

typedef struct GaugeMenu {
    void *buffers[3];
    void *packed[3];
    void *frameBuffer;
    void *framePacked;
    void *palette;
    u8 pad_24[0xb4 - 0x24];
    GaugeSlot slots[3];
} GaugeMenu;

typedef struct GaugeSave {
    u16 values[3];
    u16 limits[3];
    u8 *data;
} GaugeSave;

extern GaugeMenu *data_ov001_020a04cc;
extern GaugeLayout data_ov001_0209edf0[];
extern void func_ov001_02073cb0(void **outBuffer, void *source, u32 size);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern BOOL IsHudFlag7Set(void);
extern void func_ov001_020749c0(int a, int b, int c, int d, int e, int f);
extern void func_ov001_020747fc(int index, int x, int y, int redraw, int arg4, int arg5);

void LoadMenuGaugeData(GaugeSave *save) {
    GaugeMenu *menu = data_ov001_020a04cc;
    u8 *data = save->data;
    int i;
    GaugeLayout *layout;

    func_ov001_02073cb0(&menu->framePacked, data + 0x1c00, 0xe0);
    menu->frameBuffer = NNSi_FndAllocFromDefaultHeap(0xe0);
    menu->palette = NNSi_FndAllocFromDefaultHeap(0x40);
    MIi_CpuCopyFast(data + 0x9e0, menu->palette, 0x40);
    for (i = 0; i < 3; i++) {
        if (save->limits[i] > save->values[i]) {
            save->limits[i] = save->values[i];
        }
        menu->slots[i].maximum = save->values[i];
        menu->slots[i].target = save->values[i];
        menu->slots[i].current = 0;
        if (i == 0 && IsHudFlag7Set()) {
            layout = &data_ov001_0209edf0[i];
            func_ov001_02073cb0(&menu->packed[i], NULL, layout->size);
        } else {
            layout = &data_ov001_0209edf0[i];
            func_ov001_02073cb0(&menu->packed[i], data + data_ov001_0209edf0[i].offset, layout->size);
        }
        menu->buffers[i] = NNSi_FndAllocFromDefaultHeap(layout->size);
        if (i == 0 && IsHudFlag7Set()) {
            func_ov001_020749c0(0, 0x3c, 0x3c, 0x3c, 7, 1);
        }
        MIi_CpuCopyFast(menu->packed[i], menu->buffers[i], layout->size);
        func_ov001_020747fc(i, save->limits[i], 7, 0, 1, 0);
    }
}
