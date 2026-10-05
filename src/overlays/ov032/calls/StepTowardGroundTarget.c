#include "nitro/fx_types.h"

typedef struct {
    int header;
    u32 low : 24;
    u32 landings : 8;
} StepEntry;

typedef struct {
    u8 pad_00[4];
    s16 target;
    u8 pad_06[0x2a];
    VecFx32 bounds;
} StepUnit;

extern void ComputeGroupOrbitPosition(int angle, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL ComputePushTowardTarget(const VecFx32 *point, const VecFx32 *position, VecFx32 *bounds, VecFx32 *offset);
extern BOOL ProbeFlatGroundSquare(const VecFx32 *center, fx32 length, VecFx32 *out);

void StepTowardGroundTarget(VecFx32 *out, int angle, StepEntry *entry, StepUnit *unit,
                                     const VecFx32 *base, const VecFx32 *position)
{
    VecFx32 direction;
    VecFx32 point;
    VecFx32 offset;
    VecFx32 ground;

    ComputeGroupOrbitPosition(angle, &direction);
    VEC_Add(&direction, base, &point);
    if (unit->target == -1) {
        entry->landings = 0;
    }
    if (ComputePushTowardTarget(&point, position, &unit->bounds, &offset)) {
        VEC_Add(position, &offset, &point);
        if (ProbeFlatGroundSquare(&point, 0xc00, &ground)) {
            entry->landings++;
        }
    }
    *out = offset;
}
