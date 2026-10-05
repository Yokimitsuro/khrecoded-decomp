#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollBox {
    s32 maxX;
    s32 maxY;
    s32 maxZ;
    s32 minX;
    s32 minY;
    s32 minZ;
} CollBox;

typedef struct CollShape {
    VecFx32 *points;
    CollBox box;
    s32 kind;
} CollShape;

typedef struct CollSweep {
    CollShape shape;
    VecFx32 delta;
    CollBox sweepBox;
} CollSweep;

typedef struct ContactList {
    u8 pad_000[0x180];
    u8 count;
} ContactList;

typedef struct CollRegion {
    s32 centerX;
    s32 centerZ;
    s32 size;
} CollRegion;

typedef struct CollNode CollNode;

typedef struct CollModel {
    u8 pad_00[0x84];
    CollRegion region;
    u8 pad_90[0xc];
    CollNode *root;
    void *floorFaces;
    void *wallFaces;
    void *ceilFaces;
} CollModel;

typedef struct Mover {
    u32 flags;
    void *floorFaces;
    void *wallFaces;
    void *ceilFaces;
    u8 pad_10[0x6c];
    u8 hasSweep;
    u8 pad_7D[0x33];
    CollSweep *sweep;
    ContactList *contacts;
    u8 unk_B8;
} Mover;

typedef struct CollHitRecord {
    CollModel *model;
} CollHitRecord;

extern void ResetCollTraversal(CollModel *model);
extern void func_01ffb4f8(CollNode *root, Mover *mover, CollModel *model);
extern CollHitRecord data_027e0134;

BOOL TestMoverAgainstModel(Mover *mover, CollModel *model)
{
    BOOL inside;
    u8 prevCount;

    if (mover->hasSweep) {
        inside = mover->sweep->sweepBox.minX - model->region.centerX <= model->region.size && model->region.centerX - mover->sweep->sweepBox.maxX <= model->region.size
            && mover->sweep->sweepBox.minZ - model->region.centerZ <= model->region.size && model->region.centerZ - mover->sweep->sweepBox.maxZ <= model->region.size;
    } else {
        inside = mover->sweep->shape.box.minX - model->region.centerX <= model->region.size && model->region.centerX - mover->sweep->shape.box.maxX <= model->region.size
            && mover->sweep->shape.box.minZ - model->region.centerZ <= model->region.size && model->region.centerZ - mover->sweep->shape.box.maxZ <= model->region.size;
    }
    if (inside) {
        prevCount = mover->contacts->count;
        mover->floorFaces = model->floorFaces;
        mover->wallFaces = model->wallFaces;
        mover->ceilFaces = model->ceilFaces;
        ResetCollTraversal(model);
        func_01ffb4f8(model->root, mover, model);
        if (prevCount != mover->contacts->count) {
            data_027e0134.model = model;
            if (mover->unk_B8 == 2) {
                mover->contacts->count = 1;
            }
            return TRUE;
        }
    }
    return FALSE;
}
