#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x7ec];
    u8 backgroundLayer[0x118];
    BOOL popupOpen;
} Ov089Menu;

extern void *func_ov039_020bc1dc(void);
extern u16 *UpdateScreenWidgetLayer(int bgId);
extern void *FindWidgetById(void *panel, int elementId);
extern void SetEntrySlotsVisible(void *panel, void *element, BOOL visible);
extern void CallStateWidget(int bgId, int x, int y, int width, int height);
extern void FillBackgroundLayerRect(void *layer, u16 *dst, int x, int y, u8 palette);
extern void SetScreenLayerDirty(int bgId);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void ClosePopupWindow(Ov089Menu *menu, int soundIndex)
{
    void *panel = func_ov039_020bc1dc();
    u16 *tileMap = UpdateScreenWidgetLayer(10);

    SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xb), FALSE);
    SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xc), FALSE);
    CallStateWidget(10, 1, 0xc, 0x1e, 10);
    FillBackgroundLayerRect(menu->backgroundLayer, tileMap, 8, 0x12, 0xf);
    SetScreenLayerDirty(10);
    PlaySoundEffect(0, soundIndex);
    menu->popupOpen = FALSE;
}
