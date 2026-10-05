#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

#define INT_TO_FX32(n) ((fx32)(((f32)(n) > 0) ? (0.5f + 4096.0f * (f32)(n)) : (4096.0f * (f32)(n) - 0.5f)))

typedef float f32;

typedef struct {
    int id;
    int visibleRows;
    int totalRows;
    int panelIndex;
    int upArrowPanel;
    int downArrowPanel;
    int scrollBarPanel;
    int field_1c;
    int field_20;
    int field_24;
    int field_28;
    int topRow;
    int cursorRow;
    int barLength;
    int topMargin;
    int bottomMargin;
    int thumbMargin;
    fx32 thumbLength;
    int thumbSteps;
} ScrollList;

typedef struct {
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
} SpriteBounds;

typedef struct {
    u8 pad_00[0xcbd0];
    ScrollList lists[1];
} MenuScene;

extern SpriteBounds *GetListPanelSlotData(int screen, int panelIndex, MenuScene *scene);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern u32 AlignUpTo4K(u32 size);
extern void SetListPanelSlotFlag(int screen, int panelIndex, int value, MenuScene *scene);
extern void func_ov091_020c0164(int id, MenuScene *scene);

void InitScrollList_020bfc8c(ScrollList *template, MenuScene *scene)
{
    ScrollList *list;
    int track;
    SpriteBounds *bounds;
    int barLength;
    fx32 trackLength;
    fx32 ratio;

    list = scene->lists;
    list += template->id;
    list->id = template->id;
    list->visibleRows = template->visibleRows;
    list->totalRows = template->totalRows;
    list->panelIndex = template->panelIndex;
    list->upArrowPanel = template->upArrowPanel;
    list->downArrowPanel = template->downArrowPanel;
    list->scrollBarPanel = template->scrollBarPanel;
    list->field_1c = template->field_1c;
    list->field_20 = template->field_20;
    list->field_24 = template->field_24;
    list->field_28 = template->field_28;
    list->topRow = 0;
    list->cursorRow = 0;
    if (list->scrollBarPanel >= 0) {
        bounds = GetListPanelSlotData(list->id, list->scrollBarPanel, scene);
        barLength = bounds->top - 15 - bounds->bottom;
        list->barLength = barLength;
        list->topMargin = 8;
        list->bottomMargin = 8;
        list->thumbMargin = 8;
        track = barLength - (list->topMargin + list->bottomMargin);
        trackLength = INT_TO_FX32(track);
        ratio = FX_Div(INT_TO_FX32(list->visibleRows), INT_TO_FX32(list->totalRows));
        if (ratio > FX32_ONE) {
            ratio = FX32_ONE;
        }
        list->thumbLength = (fx32)(((s64)trackLength * ratio + 0x800) >> 12);
        list->thumbSteps = (int)AlignUpTo4K(FX_Div(list->thumbLength, 0x8000)) >> 12;
    }
    if (list->upArrowPanel >= 0) {
        SetListPanelSlotFlag(list->id, list->upArrowPanel, 0, scene);
    }
    if (list->totalRows <= list->visibleRows && list->downArrowPanel >= 0) {
        SetListPanelSlotFlag(list->id, list->downArrowPanel, 0, scene);
    }
    func_ov091_020c0164(list->id, scene);
}
