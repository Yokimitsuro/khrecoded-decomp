#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x8bc];
    u8 popupLayer[0x48];
    BOOL popupOpen;
} Ov089Menu;

extern void *func_ov039_020bc1dc(void);
extern u16 *UpdateScreenWidgetLayer(int bgId);
extern void *FindWidgetById(void *panel, int elementId);
extern void SetEntrySlotsVisible(void *panel, void *element, BOOL visible);
extern void FillBackgroundLayerRect(void *layer, u16 *dst, int x, int y, u8 palette);
extern void func_ov001_020645dc(u32 flagId);
extern void SetScreenLayerDirty(int bgId);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void OpenPopupWindow(Ov089Menu *menu)
{
    void *panel = func_ov039_020bc1dc();
    u16 *tileMap = UpdateScreenWidgetLayer(10);

    SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xb), TRUE);
    SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xc), TRUE);
    FillBackgroundLayerRect(menu->popupLayer, tileMap, 1, 0xc, 0xf);
    menu->popupOpen = TRUE;
    func_ov001_020645dc(0xff4);
    SetScreenLayerDirty(10);
    PlaySoundEffect(0, 2);
}
