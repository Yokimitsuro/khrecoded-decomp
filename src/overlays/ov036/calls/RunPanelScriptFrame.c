#include "nitro/types.h"

typedef struct PanelWork {
    u8 pad_000[0x6];
    u16 flags;
    u8 pad_008[0x8];
    u8 vm[0x1cc];
    s32 exitMode;
} PanelWork;

typedef struct PanelContext {
    u32 unk_00;
    PanelWork *work;
} PanelContext;

extern PanelContext data_ov036_020c3940;
extern int ScriptVm_RunFrame(void *vm);
extern void PcmChannel_ResetAndEnable(void *vm);

int RunPanelScriptFrame(void)
{
    PanelWork *work = data_ov036_020c3940.work;

    if (ScriptVm_RunFrame(work->vm) == 0) {
        PcmChannel_ResetAndEnable(work->vm);
        switch (work->exitMode) {
        case 0:
        case 1:
        case 2:
            data_ov036_020c3940.work->flags |= 0x8000;
            return 6;
        }
    }
    return -1;
}
