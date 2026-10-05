#include "nitro/types.h"

typedef struct {
    s32 values[5];
} ModeTable;

typedef struct {
    u8 pad_00[0x30];
    s32 active;
    u8 pad_34[4];
    s32 timer;
    u8 pad_3c[0xc];
    s32 isLanguage16;
    u8 pad_4c[0x84];
    s32 primary;
    s32 secondary;
    s32 mode;
    u8 pad_dc[4];
    s32 language;
} ModeState;

extern const ModeTable data_ov001_0209dfa8;
extern const ModeTable data_ov001_0209ef44;
extern int func_02029f6c(void);

void Panel_InitFromModeTables(ModeState *state, int mode)
{
    ModeTable primary = data_ov001_0209dfa8;
    ModeTable secondary = data_ov001_0209ef44;

    state->primary = primary.values[mode];
    state->secondary = secondary.values[mode];
    state->mode = mode;
    state->active = 1;
    state->isLanguage16 = func_02029f6c() == 0x10;
    state->language = func_02029f6c();
    state->timer = 0;
}
