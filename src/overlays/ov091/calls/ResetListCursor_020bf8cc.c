#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} TextLayer;

typedef struct {
    u16 x;
    u16 y;
    u8 pad_04[0xa];
    u16 lineSpacing;
} ListFrame;

typedef struct {
    int cursorRow;
    u8 pad_04[0x18];
    TextLayer listLayer;
    TextLayer statsLayer;
    ListFrame listFrame;
    u8 pad_94[0x60];
    u8 screenObjects[2][0x6434];
} MenuScene;

extern int GetNestedModeByte(TextLayer *layer);
extern void SetListPanelSlotPos(int screen, int panelIndex, int x, int y, MenuScene *scene);
extern void NNS_FndInitListWithOffset0_0204f130(void *list);

void ResetListCursor_020bf8cc(MenuScene *scene)
{
    int x = (scene->listFrame.x - 1) * 8;
    int y = scene->listFrame.y * 8 + 9;
    int lineHeight = GetNestedModeByte(&scene->listLayer);

    y += scene->cursorRow * (lineHeight + scene->listFrame.lineSpacing);
    SetListPanelSlotPos(0, 0, x + 4, y, scene);
    NNS_FndInitListWithOffset0_0204f130(scene->screenObjects[0]);
    NNS_FndInitListWithOffset0_0204f130(scene->screenObjects[1]);
}
