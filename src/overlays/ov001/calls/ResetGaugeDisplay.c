#include "nitro/types.h"

typedef struct GaugeContext {
    u8 pad_000[0x6c];
    u32 archive;
    u8 pad_070[0x474 - 0x70];
    s16 displayedLevel;
    u16 gauge;
    u32 isMaxed;
    u8 pad_47c[0x4];
    u32 flags;
} GaugeContext;

typedef struct GaugeGlobals {
    u32 unk_00;
    GaugeContext *context;
} GaugeGlobals;

extern GaugeGlobals data_ov001_020a04c4;

extern void func_ov001_0207b570(void);
extern BOOL IsFieldFlag13OrSessionFlagSet(void);
extern u32 func_ov001_02077bcc(void);
extern void SetFieldMenuMode(int id);
extern void *QueueFileLoadRequest(u32 path, int loadMode, void (*callback)(void *, void *), void *userData);
extern void ApplyFieldResourceAndRelease(void *request, void *userData);
extern void func_ov001_0206ed8c(u32 value);

#define LEVEL_FILE(archive, index) ((((archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | ((index) & 0x1ff))

void ResetGaugeDisplay(void)
{
    GaugeContext *context = data_ov001_020a04c4.context;

    func_ov001_0207b570();
    context->displayedLevel = IsFieldFlag13OrSessionFlagSet() ? 3 : 0;
    context->gauge = 0;
    if (func_ov001_02077bcc() == 13) {
        if (IsFieldFlag13OrSessionFlagSet()) {
            SetFieldMenuMode(7);
        } else {
            SetFieldMenuMode(0);
        }
    }
    context->flags &= ~0x10000;
    if (IsFieldFlag13OrSessionFlagSet()) {
        func_ov001_0206ed8c(context->gauge);
    } else {
        context->flags |= 0x8000;
        QueueFileLoadRequest(LEVEL_FILE(context->archive, 5), 1, ApplyFieldResourceAndRelease, NULL);
    }
    context->isMaxed = 0;
}
