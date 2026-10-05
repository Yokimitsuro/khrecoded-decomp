#include "nitro/types.h"

typedef struct EventScriptState {
    u8 pad[0x140];
    u8 vm[0x1cc];
    int phase;
    u8 pad310[0x3bd4];
    u32 taskHandle;
} EventScriptState;

extern EventScriptState *data_ov001_020a0500;
extern int ScriptVm_RunFrame(void *vm);
extern BOOL PcmChannel_ResetAndEnable(void *vm);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);
extern BOOL StartFieldSlideIn(void);
extern void StartEventCameraCut(void);
extern void func_ov001_02088330(void);
extern u32 Obj_SetWord14(u32 handle, void (*callback)(void));

BOOL RunEventScriptFrame(void) {
    EventScriptState *state = data_ov001_020a0500;

    if (ScriptVm_RunFrame(state->vm) == 0) {
        PcmChannel_ResetAndEnable(state->vm);
        switch (state->phase) {
        case 0:
        case 1:
        case 2:
            WriteSessionPackedBits(0x351f, 1, 0);
            if (StartFieldSlideIn()) {
                StartEventCameraCut();
                Obj_SetWord14(state->taskHandle, func_ov001_02088330);
                return FALSE;
            }
            break;
        }
    }
    return TRUE;
}
