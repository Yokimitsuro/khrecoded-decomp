#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollShape {
    VecFx32 *points;
    u8 pad_04[0x18];
    s32 kind;
} CollShape;

typedef struct CollSweep {
    CollShape shape;
    VecFx32 delta;
} CollSweep;

typedef struct ContactList {
    u8 pad_000[0x180];
    u8 count;
} ContactList;

typedef struct MoverParams {
    u8 pad_00[0xe];
    u16 groupMask;
    u32 ownerId;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    CollSweep *sweep;
    ContactList *contacts;
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    u8 unk_3C;
    u8 hasSweep;
    u8 isStatic;
    u8 pad_3F;
    u8 unk_40;
    u8 pad_41[3];
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
} MoverParams;

typedef struct Mover {
    u32 flags;
    u8 pad_04[0x78];
    u8 hasSweep;
    u8 isStatic;
    u8 pad_7E[0xe];
    u32 ownerId;
    u16 groupMask;
    u8 pad_92;
    u8 unk_93;
    s32 unk_94;
    s32 unk_98;
    s32 unk_9C;
    s32 unk_A0;
    s32 unk_A4;
    s32 unk_A8;
    s32 unk_AC;
    CollSweep *sweep;
    ContactList *contacts;
    u8 unk_B8;
    u8 contactCount;
    u8 pad_BA[2];
    s32 unk_BC;
    s32 unk_C0;
    s32 unk_C4;
    s32 unk_C8;
    VecFx32 direction;
    VecFx32 unitDirection;
    s8 contactPlane[16];
    s8 planeContact[16];
    s32 unk_104;
    s32 unk_108;
    s32 unk_10C;
    s32 unk_110;
} Mover;

typedef struct CollHitRecord {
    void *model;
    void *face;
    void *wallFace;
    s32 unk_0C;
    void *target;
    u8 pad_14[0x10];
    s32 nearestTime;
    u8 pad_28[0x1c];
    ContactList *contacts;
} CollHitRecord;

extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void MI_CpuFill8(void *dest, u8 data, u32 size);
extern VecFx32 data_0205344c;
extern CollHitRecord data_027e0134;

void InitMoverFromParams(Mover *mover, const MoverParams *params)
{
    VecFx32 delta;
    VecFx32 unit;

    mover->ownerId = params->ownerId;
    mover->flags = 0;
    mover->groupMask = params->groupMask;
    mover->unk_B8 = params->unk_3C;
    mover->sweep = params->sweep;
    mover->hasSweep = params->hasSweep;
    mover->isStatic = params->isStatic;
    mover->unk_104 = params->unk_2C;
    mover->unk_93 = params->unk_40;
    mover->unk_94 = params->unk_44;
    mover->unk_98 = params->unk_48;
    mover->unk_9C = params->unk_4C;
    mover->unk_BC = params->unk_50;
    mover->unk_C0 = params->unk_54;
    mover->unk_C4 = params->unk_58;
    mover->unk_C8 = params->unk_5C;
    mover->unk_A0 = params->unk_14;
    mover->unk_A4 = params->unk_18;
    mover->unk_A8 = params->unk_1C;
    mover->unk_AC = params->unk_20;
    mover->unk_108 = params->unk_30;
    mover->unk_10C = params->unk_34;
    mover->unk_110 = params->unk_38;
    mover->contactCount = params->contacts->count;

    data_027e0134.face = NULL;
    data_027e0134.wallFace = NULL;
    data_027e0134.unk_0C = 0;
    data_027e0134.target = NULL;
    mover->contacts = params->contacts;
    data_027e0134.contacts = params->contacts;
    data_027e0134.nearestTime = 0x7fffffff;

    if (params->hasSweep) {
        mover->direction = params->sweep->delta;
    } else if (params->sweep->shape.kind != 2) {
        mover->direction = data_0205344c;
    } else {
        VecFx32 *points = params->sweep->shape.points;
        func_01ff9e3c(&points[1], &points[0], &delta);
        mover->direction = delta;
    }
    func_01ffaff4(&mover->direction, &unit);
    mover->unitDirection = unit;
    MI_CpuFill8(mover->planeContact, 0xff, sizeof(mover->planeContact));
    MI_CpuFill8(mover->contactPlane, 0xff, params->contacts->count);
}
