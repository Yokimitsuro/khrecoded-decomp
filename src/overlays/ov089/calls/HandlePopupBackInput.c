#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x8fc];
    BOOL subMenuOpen;
    u8 pad_900[4];
    BOOL popupOpen;
} Ov089Menu;

extern void ClosePopupWindow(Ov089Menu *menu, int soundIndex);
extern void SetPopupConfirmMode(Ov089Menu *menu, int arg);
extern void WriteSessionPackedBits(int key, int bits, int value);
extern void SetPendingScene(int scene, int arg);
extern void StartSubScene(int a, int b, int c);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void HandlePopupBackInput(Ov089Menu *menu)
{
    if (menu->popupOpen) {
        ClosePopupWindow(menu, 3);
        return;
    }
    if (menu->subMenuOpen) {
        SetPopupConfirmMode(menu, 0);
    } else {
        WriteSessionPackedBits(0x3703, 3, 0);
        SetPendingScene(2, 0);
        StartSubScene(-1, -1, 1);
    }
    PlaySoundEffect(0, 3);
}
