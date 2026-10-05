#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotPosition {
    fx32 x;
    fx32 y;
} SlotPosition;

typedef struct ScreenPoint {
    s32 x;
    s32 y;
} ScreenPoint;

extern SlotPosition GetActorSlotPosition(int actorId);

void GetActorBalloonAnchor(ScreenPoint *outPoint, int actorId)
{
    SlotPosition position = GetActorSlotPosition(actorId);
    ScreenPoint point;

    point.x = (position.x >> 12) < 0x80 ? 0x6c : 0x94;
    if ((position.y >> 12) <= 0x80) {
        point.y = 0x19;
    } else {
        point.y = 0xa7;
    }
    *outPoint = point;
}
