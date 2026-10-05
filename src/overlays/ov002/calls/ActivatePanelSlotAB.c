#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x10];
    u8 flags10;
} PanelState;

extern PanelState *data_ov002_0206c460;
extern void DrawTextAnchored(void *context, int x, int y, int color, int flags, const void *value);

void ActivatePanelSlotAB(int param1, int x, int y, int color, const void *value) {
    if (param1 == 0) {
        DrawTextAnchored((u8 *)data_ov002_0206c460 + 0x48, x, y, color, 0, value);
        data_ov002_0206c460->flags10 |= 0x40;
        return;
    }
    DrawTextAnchored((u8 *)data_ov002_0206c460 + 0x7c, x, y, color, 0, value);
    data_ov002_0206c460->flags10 |= 0x80;
}
