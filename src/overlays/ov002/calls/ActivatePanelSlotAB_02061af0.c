#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x10];
    u8 flags10;
} PanelState;

extern PanelState *data_ov002_0206c460;
extern void DrawTextColored(void *context, int x, int y, int color, int param5, const void *param6);

void ActivatePanelSlotAB_02061af0(int param1, int x, int y, int color, int param5, const void *param6) {
    if (param1 == 0) {
        DrawTextColored((u8 *)data_ov002_0206c460 + 0x48, x, y, color, param5, param6);
        data_ov002_0206c460->flags10 |= 0x40;
        return;
    }
    DrawTextColored((u8 *)data_ov002_0206c460 + 0x7c, x, y, color, param5, param6);
    data_ov002_0206c460->flags10 |= 0x80;
}
