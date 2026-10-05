#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 x;
    fx32 y;
} PointFx32;

typedef struct {
    int x;
    int y;
    u8 pad_08[0xc];
    int id;
} SpriteSlot;

extern void IndexedRecord_SetPair(void *sprite, int id, PointFx32 *pos);

void PlaceSlotSprite(SpriteSlot *slot, void *sprite, BOOL shifted)
{
    PointFx32 pos;
    int offset;

    if (shifted) {
        offset = 0x20;
    } else {
        offset = 0;
    }
    pos.x = (slot->x - offset) << 12;
    pos.y = slot->y << 12;
    IndexedRecord_SetPair(sprite, slot->id, &pos);
}


