#include "nitro/types.h"

typedef struct ScreenSprite {
    s32 x;
    s32 y;
    s32 active;
    s32 animIndex;
    s32 palette;
    s32 spriteIndex;
} ScreenSprite;

typedef struct ItemScreen {
    u8 pad_00000[0x11ed4];
    ScreenSprite sprites[12];
} ItemScreen;

extern void *func_ov039_020bc1dc(void);
extern void func_0204f0d4(void *records, int index);
extern int PXI_Init_0204f0c8(void *records, int animIndex, int flags);
extern void IndexedRecord_SetActive(void *records, int index);
extern void func_0204f18c(void *records, int index, int value);
extern void IndexedRecord_ClearActive(void *records, int index);
extern void Slot_SetMode2Bit(void *records, int index, int mode);
extern void IndexedRecords_SetFlag2(void *records, int index, int value);
extern void func_0204f218(void *records, int index, u16 palette);
extern void PlaceSlotSprite(ScreenSprite *sprite, void *records, int param);

void SyncScreenSpriteSlots(ItemScreen *screen, int param)
{
    void *records = func_ov039_020bc1dc();
    ScreenSprite *sprite;
    int i;

    for (i = 0; i < 12; i++) {
        sprite = &screen->sprites[i];
        if (sprite->spriteIndex >= 0 && sprite->active == 0) {
            func_0204f0d4(records, sprite->spriteIndex);
            sprite->spriteIndex = -1;
        }
    }
    for (i = 0; i < 12; i++) {
        sprite = &screen->sprites[i];
        if (sprite->active != 0) {
            if (sprite->spriteIndex < 0) {
                sprite->spriteIndex = PXI_Init_0204f0c8(records, sprite->animIndex, 0);
                switch (i) {
                case 7:
                    IndexedRecord_SetActive(records, sprite->spriteIndex);
                    func_0204f18c(records, sprite->spriteIndex, 0);
                    Slot_SetMode2Bit(records, sprite->spriteIndex, 0);
                    break;
                case 8:
                case 9:
                case 10:
                case 11:
                    func_0204f18c(records, sprite->spriteIndex, 1);
                    Slot_SetMode2Bit(records, sprite->spriteIndex, 1);
                    break;
                default:
                    IndexedRecord_ClearActive(records, sprite->spriteIndex);
                    Slot_SetMode2Bit(records, sprite->spriteIndex, 2);
                    break;
                }
                IndexedRecords_SetFlag2(records, sprite->spriteIndex, 1);
            }
            if (i <= 6 && sprite->palette >= 0) {
                func_0204f218(records, sprite->spriteIndex, sprite->palette);
            }
            PlaceSlotSprite(sprite, records, param);
        }
    }
}
