#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SpritePos {
    fx32 x;
    fx32 y;
} SpritePos;

typedef struct SlotItem {
    s32 x;
    s32 y;
    s32 clipToView;
    u8 pad_0C[8];
    s32 spriteIndex;
} SlotItem;

extern void IndexedRecord_SetPair(void *sprites, int index, SpritePos *pos);
extern void IndexedRecords_SetFlag2(void *sprites, int index, BOOL visible);

void SlotMenu_PlaceItemSprite(SlotItem *item, void *sprites, BOOL rightSide, int scrollY)
{
    int offsetX = 0;
    SpritePos pos;

    if (!rightSide) {
        offsetX = 0x18;
    }
    pos.x = (item->x + offsetX) << 12;
    pos.y = (item->y - scrollY + 0x18) << 12;
    IndexedRecord_SetPair(sprites, item->spriteIndex, &pos);
    if (item->clipToView) {
        BOOL visible;
        int y = pos.y >> 12;

        if (y > 0x18 && y < 0xb4) {
            visible = TRUE;
        } else {
            visible = FALSE;
        }
        IndexedRecords_SetFlag2(sprites, item->spriteIndex, visible);
    }
}
