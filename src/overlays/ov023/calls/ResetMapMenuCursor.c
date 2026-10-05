#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MapPoint {
    fx32 x;
    fx32 y;
} MapPoint;

typedef struct MenuAnimSlot {
    int slot;
    int sequence;
} MenuAnimSlot;

typedef struct MapMenu {
    u8 pad_00[0x2c];
    BOOL dirty;
    u8 pad_30[0x28];
    u8 renderer[0x6434];
    s32 markerSlot;
    u8 pad_6490[0x4];
    s32 iconSlotA;
    s32 iconSlotB;
    u8 pad_649C[0x8];
    MenuAnimSlot cursor;
    u8 pad_64AC[0x1afc];
    fx32 position;
} MapMenu;
extern const MapPoint data_ov023_020b6eac;

extern void ChangeMenuAnimSequence(void *owner, MenuAnimSlot *anim, int sequence, u32 mode);
extern void IndexedRecord_SetPair(void *renderer, int slot, MapPoint *pos);

void ResetMapMenuCursor(MapMenu *menu)
{
    MapPoint pos = data_ov023_020b6eac;
    void *renderer = menu->renderer;

    ChangeMenuAnimSequence(renderer, &menu->cursor, 0, 0);
    IndexedRecord_SetPair(renderer, menu->cursor.slot, &pos);
    pos.x = menu->position;
    pos.y = 0x52000;
    IndexedRecord_SetPair(renderer, menu->markerSlot, &pos);
    menu->dirty = TRUE;
}
