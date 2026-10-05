#include "nitro/types.h"

typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))

typedef struct {
    u8 pad_000[0x1c];
    u8 tagPool[0x1fc - 0x1c];
    u8 textLayer[0x2cc - 0x1fc];
    u8 messageSet[0x2e4 - 0x2cc];
    u64 shownTick;
    u64 displayTicks;
} FieldManager;

typedef struct {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

extern int func_ov027_020ba33c(void *messages, const char *format, u16 *buffer, int length, va_list args);
extern void CallVirtualHandlerSlot1(void *layer, int arg);
extern void DrawTextAnchored(void *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void FlushBufferAndRunCallback(void *layer);
extern u16 *func_ov027_020b9e10(FieldManager *manager, int index);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8230(void *pool, void *record);
extern void FillBackgroundLayerRect(void *info, u16 *dst, int x, int y, u8 palette);
extern u64 OS_GetTick(void);

void ShowFieldMessageLine_02072ad0(const char *format, ...) {
    FieldManager *manager = data_ov001_020a04c4.manager;
    u16 text[0x40];
    va_list args;
    u16 *screen;

    va_start(args, format);
    func_ov027_020ba33c(manager->messageSet, format, text, 0x40, args);
    CallVirtualHandlerSlot1(manager->textLayer, 1);
    DrawTextAnchored(manager->textLayer, 0x70, 3, 2, 0x11, text);
    FlushBufferAndRunCallback(manager->textLayer);
    screen = func_ov027_020b9e10(manager, 0xb);
    func_ov027_020b8230(manager->tagPool, FindActiveRecordById(manager->tagPool, 6));
    FillBackgroundLayerRect(manager->textLayer, screen, 2, 1, 0xf);
    manager->shownTick = OS_GetTick();
    manager->displayTicks = 0x17f898;
}
