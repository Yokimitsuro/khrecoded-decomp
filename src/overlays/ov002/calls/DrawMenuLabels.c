#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PanelElement PanelElement;

typedef struct ElementPos {
    fx32 x;
    fx32 y;
} ElementPos;

typedef struct IdList {
    s32 ids[4];
} IdList;

typedef struct MenuContext {
    u8 state;
    u8 mode;
    u8 unk_02;
    s8 selectedIndex;
    u8 pad_04[0x1e];
    u8 unk_22_0 : 1;
    u8 highlightNew : 1;
    u8 unk_22_2 : 6;
    u8 pad_23[0x69e8 - 0x23];
    u8 panel[0x6450];
} MenuContext;

extern MenuContext *data_ov002_0206c464;
extern const IdList data_ov002_0206ac94;
extern const IdList data_ov002_0206aca4;
extern const IdList data_ov002_0206acb4;

extern void func_ov002_020620fc(int selector);
extern PanelElement *FindWidgetById(void *panel, int elementId);
extern void func_ov027_020b9380(void *panel, PanelElement *element, ElementPos *pos, int flag);
extern const void *func_ov002_020621c4(int index, int variant);
extern void ActivatePanelSlotCD(int param1, int x, int y, int color, const void *value);
extern int DispatchContextCommand(int kind, int index, int arg2, int arg3);
extern const void *func_ov002_02061930(void);

void DrawMenuLabels(void)
{
    u16 scratch[64] = {0};
    IdList labelIds;
    IdList modeLabelIds;
    IdList elementIds;
    ElementPos pos;
    u32 i;

    labelIds = data_ov002_0206ac94;
    modeLabelIds = data_ov002_0206aca4;
    elementIds = data_ov002_0206acb4;
    func_ov002_020620fc(-1);
    for (i = 0; i < 4; i++) {
        func_ov027_020b9380(data_ov002_0206c464->panel, FindWidgetById(data_ov002_0206c464->panel, elementIds.ids[i]), &pos, 0);
        if (labelIds.ids[i] == 0xd && data_ov002_0206c464->highlightNew) {
            ActivatePanelSlotCD(1, (pos.x >> 12) + 0x10, (pos.y >> 12) + 3, 4, func_ov002_020621c4(labelIds.ids[i], 0));
        } else {
            ActivatePanelSlotCD(1, (pos.x >> 12) + 0x10, (pos.y >> 12) + 3, 2, func_ov002_020621c4(labelIds.ids[i], 0));
        }
    }
    ActivatePanelSlotCD(1, 0x2b, 0x6e, 10, func_ov002_020621c4(DispatchContextCommand(6, 0, 0, 0), 0));
    ActivatePanelSlotCD(1, 0x2b, 0x7a, 2, func_ov002_02061930());
    ActivatePanelSlotCD(1, 8, 0xa6, 2, func_ov002_020621c4(modeLabelIds.ids[data_ov002_0206c464->selectedIndex], 0));
}
