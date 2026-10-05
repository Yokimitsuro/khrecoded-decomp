#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 x;
    s32 y;
} PanelPos;

typedef struct {
    u8 pad_00[0x94];
    u32 unk94_0 : 1;
    u32 active : 1;
} Widget;

typedef struct {
    PanelPos pos;
    u8 pad_08[0x4ac - 8];
} SlotGroup;

typedef struct {
    u8 pad_0000[0xe0];
    u8 flags0 : 6;
    u8 noSlots : 1;
    u8 pad_00e1[0x6ac0 - 0xe1];
    u8 container[0xd0a8 - 0x6ac0];
    SlotGroup groups[3];
    s32 baseY[3];
    s32 angles[3];
} PanelState;

extern PanelState *data_ov015_0207e960;
extern const s16 data_02053580[];
extern s64 _ll_sdiv(s64 numerator, s64 denominator);
extern Widget *FindWidgetById(void *root, int id);
extern BOOL IsWidgetMoveFinished(Widget *widget);
extern void SetEntrySlotsVisible(void *root, Widget *widget, int visible);
extern void ResetGroupSlotsPosition(void *manager, PanelPos *pos);
extern void func_ov027_020b9380(void *container, Widget *widget, PanelPos *pos, int flag);
extern void func_ov027_020b91e8(void *container, Widget *widget, PanelPos *pos, int flag);

void BobPanelWidgets(void) {
    PanelPos pos;
    PanelState *state;
    Widget *widget;
    int i;
    int degrees;
    fx32 fixed;
    s64 radians;
    int index;
    s32 offset;
    void *container;

    for (i = 0; i < 3; i++) {
        widget = FindWidgetById(data_ov015_0207e960->container, i + 1);
        if (widget == NULL || !widget->active) {
            continue;
        }
        if (IsWidgetMoveFinished(widget)) {
            data_ov015_0207e960->angles[i] += 4;
            data_ov015_0207e960->angles[i] %= 360;
            state = data_ov015_0207e960;
            degrees = state->angles[i];
            if (degrees > 0) {
                fixed = 0.5f + (float)(degrees << 12);
            } else {
                fixed = (float)(degrees << 12) - 0.5f;
            }
            radians = _ll_sdiv((s64)fixed * 0x3244, 0xb4000);
            index = _ll_sdiv(radians << 16, 0x6488) & 0xffff;
            func_ov027_020b9380(state->container, widget, &pos, 0);
            index >>= 4;
            offset = (s32)(((s64)data_02053580[index] * 2 + 0x800) >> 12) << 12;
            pos.y = data_ov015_0207e960->baseY[i] + offset;
            func_ov027_020b91e8(data_ov015_0207e960->container, widget, &pos, 0);
            state = data_ov015_0207e960;
            if (!state->noSlots) {
                container = state->container;
                SetEntrySlotsVisible(container, FindWidgetById(container, i + 10), 1);
            }
        }
        func_ov027_020b9380(data_ov015_0207e960->container, widget, &pos, 0);
        state = data_ov015_0207e960;
        pos.x -= 0x5000;
        pos.y -= 0x2d000;
        state->groups[i].pos = pos;
        ResetGroupSlotsPosition(state->container, &state->groups[i].pos);
    }
}
