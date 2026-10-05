#include "nitro/types.h"

typedef struct SessionFlags {
    u32 unk_0 : 9;
    u32 bit9 : 1;
    u32 unk_10 : 22;
} SessionFlags;

typedef struct Session {
    u8 pad_0000[0x214];
    SessionFlags flags;
    u8 pad_0218[0x27b6 - 0x218];
    u8 notifyOnExit : 1;
    u8 unk_27b6_1 : 7;
} Session;

extern Session *data_ov001_020a0480;
extern s32 RunSessionScriptFrame(void);
extern void func_ov001_020645e8(int bitOffset);

s32 StepSessionScriptState(void) {
    Session *session = data_ov001_020a0480;
    s32 nextState = -1;
    s32 status = RunSessionScriptFrame();

    if (status >= 0) {
        switch (status) {
        case 2:
            nextState = 3;
            break;
        case 0:
        case 1:
            nextState = 11;
            session->flags.bit9 = 0;
            break;
        }
    }
    if (nextState != -1 && session->notifyOnExit) {
        func_ov001_020645e8(0x3309);
    }
    return nextState;
}
