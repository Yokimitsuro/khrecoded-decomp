#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MapPoint {
    fx32 x;
    fx32 y;
} MapPoint;

typedef struct MapMenu {
    u8 pad_00[0x40];
    BOOL markerShown;
    u8 pad_44[0x14];
    u8 renderer[0x6444];
    s32 markerSlot;
    u8 pad_64A0[0x3d0];
    s32 maxLevel;
    u8 pad_6874[0x1740];
    BOOL distanceShown;
} MapMenu;

extern BOOL IsObjectFlagClear(void *object);
extern s32 GetFieldOffset58(void *object);
extern BOOL IsPlayerEntryFlagSet(int entry, int flag);
extern VecFx32 *func_ov001_0207f838(void *object);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void StartDistanceSqrt(const MapPoint *a, const MapPoint *b);
extern s32 SqrtResultRounded(void);
extern void ShowMapTargetDistance(MapMenu *menu, void *renderer, s32 distance);
extern void IndexedRecords_SetFlag2(void *owner, int slot, int value);

BOOL UpdateMapTargetDistance(MapMenu *menu, void *object)
{
    void *renderer = menu->renderer;
    MapPoint target;
    MapPoint origin;
    VecFx32 *targetPos;
    VecFx32 *playerPos;

    if (!IsObjectFlagClear(object) || GetFieldOffset58(object) > menu->maxLevel
        || !IsPlayerEntryFlagSet(0, 9)) {
        if (menu->distanceShown == FALSE) {
            IndexedRecords_SetFlag2(renderer, menu->markerSlot, 0);
            menu->markerShown = FALSE;
        }
        return TRUE;
    }

    targetPos = func_ov001_0207f838(object);
    playerPos = func_ov001_0206dc4c(0);
    if (playerPos == NULL) {
        return FALSE;
    }
    target.x = targetPos->x;
    target.y = targetPos->z;
    origin.x = playerPos->x;
    origin.y = playerPos->z;
    StartDistanceSqrt(&target, &origin);
    ShowMapTargetDistance(menu, renderer, SqrtResultRounded());
    menu->distanceShown = TRUE;
    return TRUE;
}
