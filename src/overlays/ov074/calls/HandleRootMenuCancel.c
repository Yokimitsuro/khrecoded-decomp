#include "nitro/types.h"

typedef struct RootMenu {
    u8 cursor;
    u8 entryCount;
    u8 state;
    u8 mode;
    u8 pad_04[0x10 - 0x04];
    u16 revealTimer;
    u16 unlockMessage;
    u8 pad_14[0x57c - 0x14];
    void *objManager;
    u8 pad_580[0x5c0 - 0x580];
    int cursorElement;
    int headerElement;
    int frameElement;
} RootMenu;

extern int func_ov039_020bc830(void);
extern void PopStackEntry(void);
extern void StartSubScene(int a, int b, int c);
extern void SetEntrySlotsVisible(void *manager, int element, BOOL visible);
extern int FindWidgetById(void *manager, int elementId);
extern void SetSecondaryElementEnabled(BOOL enabled);
extern void RuntimeState_SetCondition(int value);
extern void PlaySoundEffect(int channel, int id);
extern int IsBattleModeOne(void);
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern void SetGlobalPackedBit(int bitIndex);

void HandleRootMenuCancel(RootMenu *menu)
{
    int target;

    switch (menu->mode) {
    case 0:
        if (func_ov039_020bc830() == 1) {
            PopStackEntry();
            target = 0;
        } else {
            target = -1;
        }
        StartSubScene(target, -1, 1);
        break;
    case 1:
        SetEntrySlotsVisible(menu->objManager, menu->frameElement, FALSE);
        menu->state = 1;
        menu->mode = 0;
        break;
    case 2:
        SetEntrySlotsVisible(menu->objManager, menu->headerElement, FALSE);
        SetEntrySlotsVisible(menu->objManager, FindWidgetById(menu->objManager, 0x17), FALSE);
        menu->state = 1;
        menu->mode = 0;
        SetSecondaryElementEnabled(TRUE);
        RuntimeState_SetCondition(1);
        PlaySoundEffect(0, 1);
        if (IsBattleModeOne() && !IsGlobalPackedBitSet(0xfc3)) {
            SetGlobalPackedBit(0xfc3);
            menu->mode = 3;
            menu->unlockMessage = 0xc;
            menu->revealTimer = 0;
            SetSecondaryElementEnabled(FALSE);
            RuntimeState_SetCondition(0);
            return;
        }
        SetEntrySlotsVisible(menu->objManager, menu->cursorElement, TRUE);
        return;
    case 3:
        return;
    }
    PlaySoundEffect(0, 3);
}
