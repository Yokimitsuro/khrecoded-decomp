#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x11];
    union {
        struct {
            u8 slotCTriggered : 1;
            u8 slotDTriggered : 1;
            u8 pad_2 : 6;
        } bits;
        u8 value;
    } flags11;
} PanelState;

extern PanelState *data_ov002_0206c460;
extern void DrawTextColored(void *context, int x, int y, int color, int param5, const void *param6);

void ActivatePanelSlotCD_02061a68(int param1, int x, int y, int color, int param5, const void *param6) {
    if (param1 == 0) {
        DrawTextColored((u8 *)data_ov002_0206c460 + 0xb0, x, y, color, param5, param6);
        data_ov002_0206c460->flags11.bits.slotCTriggered = 1;
        return;
    }
    DrawTextColored((u8 *)data_ov002_0206c460 + 0xe4, x, y, color, param5, param6);
    data_ov002_0206c460->flags11.value |= 2;
}
