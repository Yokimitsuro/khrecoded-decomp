#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MapPoint {
    fx32 x;
    fx32 y;
} MapPoint;

typedef struct MapView {
    u8 pad_00[0x20];
    s32 tileScale;
    u8 pad_24[0x24];
    s32 scrollX;
    s32 scrollY;
    s32 originX;
    s32 originY;
    u8 renderer[0x6434];
    s32 markerSlot;
    s32 frameSlot;
    u8 pad_6494[0x8];
    s32 arrowSlot;
    u8 pad_64A0[0x1b18];
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    fx32 zoom;
} MapView;

extern fx32 FX_Mul(fx32 left, fx32 right);
extern void IndexedRecord_SetPair(void *renderer, int slot, MapPoint *pos);

void ScrollMapToPosition(MapView *view, const VecFx32 *worldPos)
{
    s32 mapX;
    s32 left;
    s32 top;
    fx32 screenX = 0x80000;
    fx32 screenY = 0x5c000;

    if (worldPos != NULL) {
        s32 scale = view->tileScale;
        s32 width = view->width * scale;
        s32 height = view->height * scale;
        s32 mapY;
        s32 offsetX;
        s32 offsetY;
        MapPoint pos;

        left = view->x * scale;
        top = view->y * scale;
        mapX = FX_Mul(worldPos->x * scale, view->zoom) >> 12;
        mapY = FX_Mul(worldPos->z * scale, view->zoom) >> 12;
        offsetX = 0x80 - left - mapX;

        if (width > 0xf0) {
            if (offsetX > 8) {
                screenX = (0x80 - (offsetX - 8)) << 12;
                offsetX = 8;
            } else if (offsetX + width < 0xf8) {
                s32 limit = 0xf8 - width;

                screenX = (0x80 - (offsetX - limit)) << 12;
                offsetX = limit;
            }
        } else {
            offsetX = 0x80 - width / 2;
            screenX = (mapX + (offsetX + left)) << 12;
        }

        offsetY = 0x5c - top - mapY;
        if (height > 0x78) {
            if (offsetY > 0x20) {
                screenY = (0x5c - (offsetY - 0x20)) << 12;
                offsetY = 0x20;
            } else if (offsetY + height < 0x98) {
                s32 limit = 0x98 - height;

                screenY = (0x5c - (offsetY - limit)) << 12;
                offsetY = limit;
            }
        } else {
            offsetY = 0x5c - height / 2;
            screenY = (mapY + (offsetY + top)) << 12;
        }

        view->originX = offsetX + left;
        view->originY = offsetY + top;
        view->scrollX = -offsetX;
        view->scrollY = -offsetY;
        pos.x = screenX;
        pos.y = screenY;
        IndexedRecord_SetPair(view->renderer, view->markerSlot, &pos);
        IndexedRecord_SetPair(view->renderer, view->frameSlot, &pos);
        IndexedRecord_SetPair(view->renderer, view->arrowSlot, &pos);
    }
}
