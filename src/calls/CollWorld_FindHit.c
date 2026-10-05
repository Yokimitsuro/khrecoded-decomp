#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollModel {
    u8 pad_00[0x74];
    u16 flags;
} CollModel;

typedef struct CollWorld {
    u16 pad_00;
    u16 modelCount;
    CollModel **models;
} CollWorld;

typedef struct CollSweep {
    VecFx32 *points;
} CollSweep;

typedef struct Mover {
    u8 pad_00[0xb0];
    CollSweep *sweep;
    u8 pad_B4[0x60];
} Mover;

typedef struct CollHitRecord {
    u8 pad_00[0x38];
    VecFx32 origin;
} CollHitRecord;

extern void InitMoverFromParams(Mover *mover, const void *params);
extern BOOL TestMoverAgainstModel(Mover *mover, CollModel *model);
extern CollHitRecord data_027e0134;

CollHitRecord *CollWorld_FindHit(CollWorld *world, const void *params)
{
    Mover mover;
    BOOL hit = FALSE;
    int i;
    int count = world->modelCount;

    InitMoverFromParams(&mover, params);
    for (i = 0; i < count; i++) {
        if ((world->models[i]->flags & 0x2000) == 0) {
            if (TestMoverAgainstModel(&mover, world->models[i])) {
                hit = TRUE;
            }
        }
    }
    if (!hit) {
        return NULL;
    }
    data_027e0134.origin = *mover.sweep->points;
    return &data_027e0134;
}
