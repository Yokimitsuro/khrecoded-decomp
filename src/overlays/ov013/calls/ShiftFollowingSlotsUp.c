#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PanelPos {
    fx32 x;
    fx32 y;
} PanelPos;

typedef struct PanelElement {
    u8 pad_00[0x34];
    PanelPos position;
    u8 pad_3c[0x94 - 0x3c];
    u32 unk_94_0 : 1;
    u32 isActive : 1;
} PanelElement;

typedef struct PanelState {
    u8 pad_00[0x9c];
    PanelPos slotTargets[9];
    PanelPos frameTargets[9];
    PanelPos rowTargets[9];
    PanelPos highIdTargets[9];
    PanelPos lowIdTargets[9];
    u8 pad_204[0x2dc - 0x204];
    int unk_2DC;
    u8 pad_2e0[0x2ee - 0x2e0];
    s8 currentIndex;
    u8 pad_2ef[0x6818 - 0x2ef];
    u8 panel[0xd150 - 0x6818];
    PanelElement *slotElements[9];
    PanelElement *frameElements[9];
    PanelElement *rowElements[9 * 3];
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern PanelElement *FindWidgetById(void *panel, int id);
extern void func_ov027_020b9380(void *panel, PanelElement *element, PanelPos *out, int mode);
extern void StartWidgetMoveTween(void *panel, PanelElement *element, int mode, PanelPos *from, PanelPos *to, int duration);
extern void SetWidgetRootTouchEnabled(void *panel, BOOL enable);

void ShiftFollowingSlotsUp(void) {
    PanelPos pos;
    PanelElement *element;
    int index;

    data_ov013_02074ce0->unk_2DC = 0;
    for (index = data_ov013_02074ce0->currentIndex + 1; index < 9; index++) {
        element = data_ov013_02074ce0->slotElements[index];
        if (element->isActive) {
            StartWidgetMoveTween(data_ov013_02074ce0->panel, element, 2, &element->position,
                                &data_ov013_02074ce0->slotTargets[index - 1], 500);
            element = data_ov013_02074ce0->frameElements[index];
            StartWidgetMoveTween(data_ov013_02074ce0->panel, element, 2, &element->position,
                                &data_ov013_02074ce0->frameTargets[index - 1], 500);
            element = FindWidgetById(data_ov013_02074ce0->panel, index + 200);
            StartWidgetMoveTween(data_ov013_02074ce0->panel, element, 2, &element->position,
                                &data_ov013_02074ce0->highIdTargets[index - 1], 500);
            element = FindWidgetById(data_ov013_02074ce0->panel, index + 100);
            StartWidgetMoveTween(data_ov013_02074ce0->panel, element, 2, &element->position,
                                &data_ov013_02074ce0->lowIdTargets[index - 1], 500);

            func_ov027_020b9380(data_ov013_02074ce0->panel, data_ov013_02074ce0->rowElements[index * 3], &pos, 0);
            pos.y = data_ov013_02074ce0->rowTargets[index - 1].y;
            element = data_ov013_02074ce0->rowElements[index * 3];
            StartWidgetMoveTween(data_ov013_02074ce0->panel, element, 2, &element->position, &pos, 500);
            func_ov027_020b9380(data_ov013_02074ce0->panel, data_ov013_02074ce0->rowElements[index * 3 + 1], &pos, 0);
            pos.y = data_ov013_02074ce0->rowTargets[index - 1].y;
            element = data_ov013_02074ce0->rowElements[index * 3 + 1];
            StartWidgetMoveTween(data_ov013_02074ce0->panel, element, 2, &element->position, &pos, 500);
            func_ov027_020b9380(data_ov013_02074ce0->panel, data_ov013_02074ce0->rowElements[index * 3 + 2], &pos, 0);
            pos.y = data_ov013_02074ce0->rowTargets[index - 1].y;
            element = data_ov013_02074ce0->rowElements[index * 3 + 2];
            StartWidgetMoveTween(data_ov013_02074ce0->panel, element, 2, &element->position, &pos, 500);
        }
    }
    SetWidgetRootTouchEnabled(data_ov013_02074ce0->panel, FALSE);
}
