#include "nitro/types.h"

typedef struct CollBox {
    s32 maxX;
    s32 maxY;
    s32 maxZ;
    s32 minX;
    s32 minY;
    s32 minZ;
} CollBox;

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

typedef struct CollGatherQuery {
    u8 pad_00[4];
    void *floorFaces;
    void *wallFaces;
    void *ceilFaces;
    u8 pad_10[0xa0 - 0x10];
    CollBox *box;
} CollGatherQuery;

extern void ResetCollTraversal(CollModel *model);
extern void func_02031478(CollNode *root, CollGatherQuery *query, CollModel *model);

void GatherModelFaces(CollGatherQuery *query, CollModel *model)
{
    CollBox *box = query->box;

    if (box->minX - model->region.centerX <= model->region.size && model->region.centerX - box->maxX <= model->region.size
        && box->minZ - model->region.centerZ <= model->region.size && model->region.centerZ - box->maxZ <= model->region.size) {
        query->floorFaces = model->floorFaces;
        query->wallFaces = model->wallFaces;
        query->ceilFaces = model->ceilFaces;
        ResetCollTraversal(model);
        func_02031478(model->root, query, model);
    }
}
