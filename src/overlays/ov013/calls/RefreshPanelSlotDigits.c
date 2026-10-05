#include "nitro/types.h"

typedef struct PanelObject {
    u8 pad_00[0x14];
    s32 slotId;
    u8 pad_18[0x94 - 0x18];
    u32 flags;
} PanelObject;

typedef struct PanelState {
    u8 pad_00[0x2ec];
    s8 lastIndex;
    u8 pad_2ed[2];
    s8 firstIndex;
    u8 pad_2f0[0x6818 - 0x2f0];
    u8 panel[0xd150 - 0x6818];
    PanelObject *frameObjects[9];
    PanelObject *iconObjects[9];
    PanelObject *digitObjects[27];
} PanelState;

typedef struct ContextInfo {
    u8 pad_00[0x68];
    u8 iconFrame;
    u8 pad_69;
    u8 labelVisible;
    u8 pad_6b[5];
} ContextInfo;

extern PanelState *data_ov013_02074ce0;
extern PanelObject *FindWidgetById(void *panel, int id);
extern void SetEntrySlotsVisible(void *panel, PanelObject *object, int visible);
extern void func_ov027_020b96c0(void *panel, PanelObject *object, u16 frame);
extern void SlotTable_SetEntryPriority(void *panel, s32 slotId, int priority);
extern u32 DispatchContextCommand(u32 command, u32 value, u32 extra, void *buffer);
extern void func_ov013_02070ce8(void);

void RefreshPanelSlotDigits(void)
{
    int start;
    int slot;
    int span;
    int offset;
    int value;
    int digit;
    int total;
    int entry;
    int count;
    PanelState *state;
    u8 *panel;
    PanelObject *object;
    ContextInfo info;

    for (slot = 0; slot < 9; slot++) {
        SetEntrySlotsVisible(data_ov013_02074ce0->panel, data_ov013_02074ce0->iconObjects[slot], 0);
        SetEntrySlotsVisible(data_ov013_02074ce0->panel, data_ov013_02074ce0->frameObjects[slot], 0);
        state = data_ov013_02074ce0;
        panel = state->panel;
        object = FindWidgetById(panel, slot + 200);
        SetEntrySlotsVisible(panel, object, 0);
        state = data_ov013_02074ce0;
        panel = state->panel;
        object = FindWidgetById(panel, slot + 100);
        SetEntrySlotsVisible(panel, object, 0);
        SetEntrySlotsVisible(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitObjects[slot * 3 + 0], 0);
        SetEntrySlotsVisible(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitObjects[slot * 3 + 1], 0);
        SetEntrySlotsVisible(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitObjects[slot * 3 + 2], 0);
    }

    start = 0;
    if (data_ov013_02074ce0->firstIndex == 0) {
        start = 1;
    }
    span = data_ov013_02074ce0->lastIndex - data_ov013_02074ce0->firstIndex;
    for (slot = start; slot < 9; slot++) {
        if (slot < span + 1) {
            SetEntrySlotsVisible(data_ov013_02074ce0->panel, data_ov013_02074ce0->iconObjects[slot], 1);
            SetEntrySlotsVisible(data_ov013_02074ce0->panel, data_ov013_02074ce0->frameObjects[slot], 1);
            digit = 0;
            value = data_ov013_02074ce0->firstIndex + slot;
            do {
                func_ov027_020b96c0(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitObjects[slot * 3 + digit], value % 10);
                SetEntrySlotsVisible(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitObjects[slot * 3 + digit], 1);
                digit++;
                value /= 10;
            } while (value != 0);
        }
    }

    count = 0;
    total = DispatchContextCommand(7, 0, 0, 0);
    offset = data_ov013_02074ce0->firstIndex;
    if (offset != 0) {
        offset--;
    }
    for (; start < 9; start++) {
        if ((data_ov013_02074ce0->frameObjects[start]->flags << 30) >> 31) {
            entry = offset + count;
            if ((entry + 1) % 10 == 0) {
                if (total + 1 <= entry) {
                    SetEntrySlotsVisible(data_ov013_02074ce0->panel, data_ov013_02074ce0->iconObjects[start], 1);
                    SlotTable_SetEntryPriority(data_ov013_02074ce0->panel, data_ov013_02074ce0->iconObjects[start]->slotId, 10);
                    SlotTable_SetEntryPriority(data_ov013_02074ce0->panel, data_ov013_02074ce0->frameObjects[start]->slotId, 2);
                    SlotTable_SetEntryPriority(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitObjects[start * 3 + 0]->slotId, 2);
                    SlotTable_SetEntryPriority(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitObjects[start * 3 + 1]->slotId, 2);
                    SlotTable_SetEntryPriority(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitObjects[start * 3 + 2]->slotId, 2);
                } else {
                    SlotTable_SetEntryPriority(data_ov013_02074ce0->panel, data_ov013_02074ce0->iconObjects[start]->slotId, 9);
                    SlotTable_SetEntryPriority(data_ov013_02074ce0->panel, data_ov013_02074ce0->frameObjects[start]->slotId, 1);
                    SlotTable_SetEntryPriority(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitObjects[start * 3 + 0]->slotId, 1);
                    SlotTable_SetEntryPriority(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitObjects[start * 3 + 1]->slotId, 1);
                    SlotTable_SetEntryPriority(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitObjects[start * 3 + 2]->slotId, 1);
                }
                func_ov027_020b96c0(data_ov013_02074ce0->panel, data_ov013_02074ce0->iconObjects[start], 4);
                value = DispatchContextCommand(10, entry + 1, 0, 0);
                state = data_ov013_02074ce0;
                panel = state->panel;
                object = FindWidgetById(panel, start + 100);
                SetEntrySlotsVisible(panel, object, value);
            } else {
                if (total + 1 <= entry) {
                    SlotTable_SetEntryPriority(data_ov013_02074ce0->panel, data_ov013_02074ce0->iconObjects[start]->slotId, 10);
                    SlotTable_SetEntryPriority(data_ov013_02074ce0->panel, data_ov013_02074ce0->frameObjects[start]->slotId, 2);
                    SlotTable_SetEntryPriority(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitObjects[start * 3 + 0]->slotId, 2);
                    SlotTable_SetEntryPriority(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitObjects[start * 3 + 1]->slotId, 2);
                    SlotTable_SetEntryPriority(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitObjects[start * 3 + 2]->slotId, 2);
                } else {
                    SlotTable_SetEntryPriority(data_ov013_02074ce0->panel, data_ov013_02074ce0->iconObjects[start]->slotId, 8);
                    SlotTable_SetEntryPriority(data_ov013_02074ce0->panel, data_ov013_02074ce0->frameObjects[start]->slotId, 1);
                    SlotTable_SetEntryPriority(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitObjects[start * 3 + 0]->slotId, 1);
                    SlotTable_SetEntryPriority(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitObjects[start * 3 + 1]->slotId, 1);
                    SlotTable_SetEntryPriority(data_ov013_02074ce0->panel, data_ov013_02074ce0->digitObjects[start * 3 + 2]->slotId, 1);
                }
                DispatchContextCommand(0, entry - (entry + 1) / 10, 0, &info);
                func_ov027_020b96c0(data_ov013_02074ce0->panel, data_ov013_02074ce0->iconObjects[start], info.iconFrame);
                state = data_ov013_02074ce0;
                panel = state->panel;
                object = FindWidgetById(panel, start + 100);
                SetEntrySlotsVisible(panel, object, info.labelVisible);
            }
            count++;
        }
    }
    func_ov013_02070ce8();
}
