#include "nitro/types.h"

typedef struct SessionScript {
    u8 pad_000[0x1cc];
    s32 status;
    u8 pad_1d0[0x828 - 0x1d0];
    s8 runFlags;
} SessionScript;

typedef struct Session {
    u8 pad_0000[0x1f10];
    SessionScript script;
} Session;

extern Session *data_ov001_020a0480;
extern int ScriptVm_RunFrame(SessionScript *vm);
extern BOOL PcmChannel_ResetAndEnable(SessionScript *vm);

s32 RunSessionScriptFrame(void) {
    SessionScript *script = &data_ov001_020a0480->script;
    script->runFlags |= 1;
    if (ScriptVm_RunFrame(script) == 0) {
        PcmChannel_ResetAndEnable(script);
        script->runFlags = 0;
        return script->status;
    }
    return -1;
}
