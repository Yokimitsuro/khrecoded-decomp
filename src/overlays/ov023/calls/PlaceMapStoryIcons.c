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
extern BOOL func_ov001_020645c8(u32 flag);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void WorldToMapPosition(MapMenu *menu, MapPoint *out, const VecFx32 *worldPos);
extern void IndexedRecord_SetPair(void *renderer, int slot, MapPoint *pos);

void PlaceMapStoryIcons(MapMenu *menu)
{
    void *renderer = menu->renderer;
    MapPoint pos;

    if (func_ov001_020645c8(0x3609)) {
        WorldToMapPosition(menu, &pos, func_ov001_0206dc4c(1));
        IndexedRecord_SetPair(renderer, menu->iconSlotA, &pos);
    }
    if (func_ov001_020645c8(0x360a)) {
        WorldToMapPosition(menu, &pos, func_ov001_0206dc4c(2));
        IndexedRecord_SetPair(renderer, menu->iconSlotB, &pos);
    }
}
