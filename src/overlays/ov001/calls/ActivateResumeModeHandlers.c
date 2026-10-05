#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u8 handlers[0xa8 - 0xc];
    u16 stageId;
    u8 pad_aa[2];
    int state;
} ModeBlock;

typedef struct {
    u8 pad_000[0x214];
    u32 lowFlags : 14;
    u32 resumeFlag : 1;
    u32 highFlags : 17;
    u8 pad_218[4];
    int stageId;
    u8 pad_220[0x27ec - 0x220];
    int defaultState;
    u8 pad_27f0[0x2800 - 0x27f0];
    ModeBlock mode;
} Session;

extern Session *data_ov001_020a0480;
extern void InstallResumeModeHandlers(void *handlers);

void ActivateResumeModeHandlers(void) {
    Session *session = data_ov001_020a0480;
    ModeBlock *mode = &session->mode;
    int state;
    if (session->resumeFlag) {
        mode->stageId = session->stageId;
        state = 7;
    } else {
        state = session->defaultState;
    }
    mode->state = state;
    InstallResumeModeHandlers(mode->handlers);
}
