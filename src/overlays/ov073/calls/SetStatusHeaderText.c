#include "nitro/types.h"

typedef struct MenuSharedState {
    s8 selectedIndex;
    u8 pad_01;
    u8 refreshCount;
    u8 flags;
    u8 pad_04[0xe5c - 4];
    u16 shortText[2][0x20];
    u16 longText[2][0x70];
} MenuSharedState;

extern const u16 data_ov073_020c41a0[];
extern MenuSharedState *func_ov039_020bc650(void);
extern int OS_SNPrintf_0202e094(u16 *dst, u32 length, const u16 *format, ...);

void SetStatusHeaderText(const u16 *shortText, const u16 *longText)
{
    MenuSharedState *state = func_ov039_020bc650();
    int page;

    if (state->flags & 2) {
        page = 1;
    } else {
        page = 0;
    }
    if (longText != NULL) {
        if (shortText != NULL) {
            OS_SNPrintf_0202e094(state->shortText[page], 0x20, data_ov073_020c41a0, shortText);
        } else {
            state->shortText[page][0] = 0;
        }
        OS_SNPrintf_0202e094(state->longText[page], 0x70, data_ov073_020c41a0, longText);
    } else {
        state->shortText[page][0] = 0;
        state->longText[page][0] = 0;
    }
    if (state->refreshCount == 0) {
        state->refreshCount++;
    }
}
