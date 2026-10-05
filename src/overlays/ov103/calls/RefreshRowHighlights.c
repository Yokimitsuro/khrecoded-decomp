#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2C];
    s32 scroll;
} ScrollPanel;

typedef struct {
    u8 pad_0000[0xCACC];
    ScrollPanel panel;
} Ov103State;

extern BOOL IsEntryFlagSet_020c01a0(int flagSet, int entryIndex);
extern void SetSlotEntryVisible(int listIndex, int entryIndex, int visible, Ov103State *state);

void RefreshRowHighlights(Ov103State *state)
{
    ScrollPanel *panel = &state->panel;
    int i;

    for (i = 0; i < 9; i++) {
        if (IsEntryFlagSet_020c01a0(1, i + panel->scroll)) {
            SetSlotEntryVisible(0, i + 3, 1, state);
        } else {
            SetSlotEntryVisible(0, i + 3, 0, state);
        }
    }
}
