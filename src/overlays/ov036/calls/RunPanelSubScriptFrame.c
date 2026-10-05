#include "nitro/types.h"

typedef struct PanelWork {
    u8 pad_000[0x6];
    u16 flags;
    u8 pad_008[0x650];
    u8 subVm[0x1cc];
    s32 exitMode;
} PanelWork;

typedef struct PanelContext {
    u32 unk_00;
    PanelWork *work;
} PanelContext;

extern PanelContext data_ov036_020c3940;
extern int ScriptVm_RunFrame(void *vm);
extern void PcmChannel_ResetAndEnable(void *vm);

int RunPanelSubScriptFrame(void)
{
    PanelWork *work = data_ov036_020c3940.work;

    if (ScriptVm_RunFrame(work->subVm) == 0) {
        PcmChannel_ResetAndEnable(work->subVm);
        switch (work->exitMode) {
        case 0:
        case 1:
        case 2:
            data_ov036_020c3940.work->flags |= 0x8000;
            return 5;
        }
    }
    return -1;
}
