#include "nitro/types.h"

typedef struct MenuContext {
    u8 pad_00[0x4];
    int scrollX;
    u8 pad_08[0x4];
    int scrollY;
    int offsetY;
    int offsetX;
    u8 pad_18[0x18];
    void *paletteA;
    void *paletteB;
} MenuContext;

extern MenuContext *data_ov001_020a04f0;
extern void *func_ov001_0207123c(void);
extern void *GetSceneTagTracker(void);
extern void func_ov027_020b9d74(void *widgets, int layer, int x, int y, int width, int height);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8288(void *pool, void *record);
extern int NNS_GfdRegisterNewVramTransferTask(int command, int offset, void *data, int size);

void ResetMenuScreenLayers(void)
{
    MenuContext *context = data_ov001_020a04f0;
    void *widgets = func_ov001_0207123c();
    void *pool = GetSceneTagTracker();

    context->scrollX = 0;
    context->scrollY = 0;
    context->offsetX = 0;
    context->offsetY = 0;
    func_ov027_020b9d74(widgets, 0xb, 0xe, 0, 4, 2);
    func_ov027_020b9d74(widgets, 0xb, 0xf, 0x13, 2, 3);
    func_ov027_020b8288(pool, FindActiveRecordById(pool, 300));
    func_ov027_020b8288(pool, FindActiveRecordById(pool, 308));
    func_ov027_020b8288(pool, FindActiveRecordById(pool, 302));
    func_ov027_020b8288(pool, FindActiveRecordById(pool, 305));
    func_ov027_020b8288(pool, FindActiveRecordById(pool, 306));
    func_ov027_020b8288(pool, FindActiveRecordById(pool, 307));
    func_ov027_020b8288(pool, FindActiveRecordById(pool, 311));
    *(vu16 *)0x0400000e = (u16)((*(vu16 *)0x0400000e & ~3) | 2);
    *(vu16 *)0x0400000c = (u16)((*(vu16 *)0x0400000c & ~3) | 1);
    NNS_GfdRegisterNewVramTransferTask(0xf, 0x1a0, context->paletteA, 0x20);
    NNS_GfdRegisterNewVramTransferTask(0xf, 0x1c0, context->paletteB, 0x20);
}
