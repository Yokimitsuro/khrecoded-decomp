#include "nitro/types.h"

typedef struct SessionScript {
    u8 pad_000[0x820];
    u32 paramA;
    u32 paramB;
} SessionScript;

typedef struct Session {
    u8 pad_0000[0x1f10];
    SessionScript script;
} Session;

extern Session *data_ov001_020a0480;

void SetSessionScriptParams(u32 paramA, u32 paramB) {
    SessionScript *script = &data_ov001_020a0480->script;
    script->paramA = paramA;
    script->paramB = paramB;
}
