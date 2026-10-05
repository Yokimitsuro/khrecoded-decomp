#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x1c];
    u32 selection;
    u32 *choices;
} PanelState;

void PanelState_SelectChoice(u32 index, PanelState *state)
{
    u32 *choices = state->choices;

    if (index <= 2) {
        int slot = index - 1;
        state->selection = (u8)choices[slot];
    }
}
