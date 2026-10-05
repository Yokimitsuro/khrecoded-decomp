#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 position;
    s32 paramA;
    s32 paramB;
} PathPoint;

typedef struct {
    u32 index : 10;
    u32 flags : 22;
    VecFx32 position;
    s32 paramA;
    s32 paramB;
} PathPointSource;

typedef struct {
    u8 pad_00[0xbc];
    PathPoint *points;
} FieldUnit;

void SetFieldUnitPathPoint(FieldUnit *unit, PathPointSource *src)
{
    PathPoint *point = &unit->points[src->index];

    point->position = src->position;
    point->paramA = src->paramA;
    point->paramB = src->paramB;
}
