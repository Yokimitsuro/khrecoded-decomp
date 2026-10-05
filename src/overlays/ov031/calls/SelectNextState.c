#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
    u8 pad_08[0x34];
    s8 mode;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern void func_ov001_0206e444(BOOL paused);
extern void PlaySoundChecked(void *ptr, int arg);
extern BOOL IsEntryFlag2Active(int index);
extern void func_0204d808(int value);
extern u32 func_ov001_0206e644(void);

s32 SelectNextState(void)
{
    OverlayState *state = data_ov031_020bc820;

    if (state->flags & 0x4000) {
        func_ov001_0206e444(TRUE);
        data_ov031_020bc820->flags |= 0x8000;
        return 14;
    }
    if (state->flags & 0x12) {
        return -1;
    }
    if (state->flags & 0x40) {
        PlaySoundChecked(NULL, 0x4e);
        data_ov031_020bc820->flags |= 0x8000;
        return 13;
    }
    if (state->mode >= 0) {
        return 9;
    }
    if (IsEntryFlag2Active(0)) {
        data_ov031_020bc820->flags |= 0x10;
        func_0204d808(0x20);
        return 11;
    }
    if (func_ov001_0206e644()) {
        func_ov001_0206e444(TRUE);
        return 8;
    }
    return -1;
}



