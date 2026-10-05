#include "nitro/types.h"

typedef struct ContextSlot {
    u8 data[0x4c];
} ContextSlot;

typedef struct ContextConfig {
    ContextSlot slots[0x5a];
    u8 pad_1ab8[0x1ac8 - 0x1ab8];
    u32 slotCount : 7;
    u32 unk_1ac8_b7 : 25;
} ContextConfig;

extern ContextConfig *func_ov002_02066fe0(void);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

void RemoveContextSlot(int index)
{
    int i;
    ContextConfig *config;
    int remaining;

    config = func_ov002_02066fe0();
    remaining = config->slotCount - index;
    for (i = 0; i < remaining; i++) {
        MI_CpuCopy8(&config->slots[index + i + 1], &config->slots[index + i], sizeof(ContextSlot));
    }
    config->slotCount--;
}
