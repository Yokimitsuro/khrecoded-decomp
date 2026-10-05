#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2C];
    s32 scroll;
    s32 cursor;
} ScrollPanel;

typedef struct {
    s32 selection;
    u8 pad_0004[0xCACC - 4];
    ScrollPanel panel;
} Ov103State;

extern int func_ov103_020c032c(Ov103State *state);
extern BOOL ScrollListUp_020bfc20(int panelIndex, Ov103State *state);
extern void func_ov103_020bf0c4(Ov103State *state);
extern void func_ov103_020bf3bc(int which, Ov103State *state);
extern void RefreshRowHighlights(Ov103State *state);
extern void PlaySoundEffect(int soundId, int arg);

void HandleListScrollDown(Ov103State *state)
{
    ScrollPanel *panel;

    if (func_ov103_020c032c(state) != 3) {
        return;
    }
    if (!ScrollListUp_020bfc20(0, state)) {
        return;
    }
    panel = &state->panel;
    state->selection = panel->scroll + panel->cursor;
    func_ov103_020bf0c4(state);
    func_ov103_020bf3bc(0, state);
    RefreshRowHighlights(state);
    PlaySoundEffect(0, 0);
}
