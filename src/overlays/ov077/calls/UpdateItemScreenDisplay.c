#include "nitro/types.h"

typedef struct ScreenSprite {
    s32 x;
    s32 y;
    s32 unk_08;
    s32 animIndex;
    s32 unk_10;
    s32 spriteIndex;
} ScreenSprite;

typedef struct ItemScreen {
    u8 pad_00000[0x1c];
    s32 targetPage;
    u8 pad_00020[0x11ed0 - 0x20];
    s32 mode;
    ScreenSprite sprites[12];
    s32 state;
    s32 category;
    u8 pad_11ffc[4];
    s32 page;
} ItemScreen;

extern BOOL func_ov039_020bc0f4(void);
extern void *func_ov039_020bc1dc(void);
extern void IndexedRecords_SetFlag2(void *recordArray, int recordIndex, BOOL active);
extern BOOL func_ov077_020c53c0(ItemScreen *screen);
extern void ShowSlotHeaderMessage(ItemScreen *screen);
extern void SetPanelShifted(ItemScreen *screen, BOOL firstPage);
extern void func_ov077_020c45b8(ItemScreen *screen);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void func_ov077_020c5814(ItemScreen *screen, int arg);
extern void SyncScreenSpriteSlots(ItemScreen *screen, int arg);
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern void PlaceElement42OrHide(void *container, const s32 *position);

void UpdateItemScreenDisplay(ItemScreen *screen)
{
    s32 position[2];
    s32 *positionPtr;
    BOOL visible;
    ScreenSprite *pageSprite = &screen->sprites[7];

    if (pageSprite->spriteIndex >= 0) {
        BOOL active;
        if (func_ov039_020bc0f4() != 0 && screen->mode == 0) {
            active = TRUE;
        } else {
            active = FALSE;
        }
        IndexedRecords_SetFlag2(func_ov039_020bc1dc(), pageSprite->spriteIndex, active);
    }

    if (func_ov077_020c53c0(screen) == 0) {
        switch (screen->mode) {
        case 0:
            *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0x1d00;
            *(vu16 *)0x0400000a = (*(vu16 *)0x0400000a & 0x43) | 0x90;
            *(vu32 *)0x04000018 = 0;
            ShowSlotHeaderMessage(screen);
            break;
        case 1:
            *(vu32 *)0x04000018 = 0x1c;
            SetPanelShifted(screen, TRUE);
            break;
        case 2:
            func_ov077_020c45b8(screen);
            PlaySoundEffect(1, 5);
        case 3:
            func_ov077_020c5814(screen, 0);
            SyncScreenSpriteSlots(screen, 0);
            break;
        }
    } else {
        BOOL changed;
        if (screen->page != screen->targetPage) {
            screen->page ^= 1;
            changed = TRUE;
        } else {
            changed = FALSE;
        }
        if (changed) {
            SetPanelShifted(screen, screen->page == 0);
        }
    }

    if (screen->mode == 0) {
        switch (screen->category) {
        case 0:
            visible = !IsGlobalPackedBitSet(0xf93);
            position[0] = 0x40000;
            position[1] = 0x20000;
            break;
        case 1:
            visible = !IsGlobalPackedBitSet(0xf99);
            position[0] = 0x48000;
            position[1] = 0x30000;
            break;
        default:
            visible = !IsGlobalPackedBitSet(0xf9a);
            position[0] = 0x40000;
            position[1] = ((screen->category - 2) * 16 + 0x58) << 12;
            break;
        }
        positionPtr = position;
        if (!visible) {
            positionPtr = NULL;
        }
        PlaceElement42OrHide(func_ov039_020bc1dc(), positionPtr);
    } else {
        PlaceElement42OrHide(func_ov039_020bc1dc(), NULL);
    }
}
