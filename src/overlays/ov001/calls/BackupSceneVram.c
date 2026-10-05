#include "nitro/types.h"

typedef struct HudContext {
    u8 pad_000[0x448];
    void *bgVramBackup;
    void *bg2CharBackup;
    void *widgetLayerBackups[3];
    void *paletteBackup;
} HudContext;

typedef struct WidgetLayerIds {
    int ids[3];
} WidgetLayerIds;

extern const WidgetLayerIds data_ov001_0209dbe0;
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void *G2_GetBG2CharPtr(void);
extern void *func_ov001_0207123c(void);
extern void *func_ov027_020b9e10(void *widgets, int layer);

static inline BOOL DisableIrq(void)
{
    u16 previous = *(vu16 *)0x04000208;
    *(vu16 *)0x04000208 = 0;
    return previous;
}

static inline BOOL EnableIrq(void)
{
    u16 previous = *(vu16 *)0x04000208;
    *(vu16 *)0x04000208 = 1;
    return previous;
}

void BackupSceneVram(HudContext *context)
{
    WidgetLayerIds layers = data_ov001_0209dbe0;
    BOOL irqEnabled;
    void *buffer;
    void *layer;
    int i;

    irqEnabled = DisableIrq();
    context->bgVramBackup = NNS_FndAllocFromDefaultExpHeapEx(0x5b00, -0x20);
    MIi_CpuCopyFast((void *)0x06000000, context->bgVramBackup, 0x5b00);
    buffer = NNS_FndAllocFromDefaultExpHeapEx(0x1000, -0x20);
    context->bg2CharBackup = buffer;
    MIi_CpuCopyFast(G2_GetBG2CharPtr(), buffer, 0x1000);
    for (i = 0; i < 3; i++) {
        context->widgetLayerBackups[i] = NNS_FndAllocFromDefaultExpHeapEx(0x800, -0x20);
        buffer = context->widgetLayerBackups[i];
        layer = func_ov027_020b9e10(func_ov001_0207123c(), layers.ids[i]);
        MIi_CpuCopyFast(layer, buffer, 0x800);
    }
    context->paletteBackup = NNS_FndAllocFromDefaultExpHeapEx(0x200, -0x20);
    MIi_CpuCopyFast((void *)0x05000000, context->paletteBackup, 0x200);
    if (irqEnabled) {
        EnableIrq();
    }
}
