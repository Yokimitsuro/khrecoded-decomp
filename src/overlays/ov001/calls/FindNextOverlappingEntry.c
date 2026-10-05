#include "nitro/types.h"

typedef struct {
    s32 pad_00;
    s32 maxX;
    s32 maxY;
    s32 maxZ;
    s32 minX;
    s32 minY;
    s32 minZ;
    s32 shape;
} CollisionVolume;

typedef struct CollisionEntity CollisionEntity;
struct CollisionEntity {
    u8 pad_000[0x220];
    BOOL (*getVolume)(CollisionEntity *entity, CollisionVolume *volume);
};

typedef BOOL (*ShapeTestFunc)(CollisionVolume *a, CollisionVolume *b, void *arg, int flags);

typedef struct {
    u8 pad_00[0x7c];
    s32 count;
    u8 pad_80[0x78];
    s32 cursor;
} CollisionManager;

extern CollisionManager *data_ov001_020a04bc;
extern ShapeTestFunc gCollisionTestPairDispatch[][6];
extern CollisionEntity *GetBoundedEntryField(int index);

CollisionEntity *FindNextOverlappingEntry(CollisionVolume *query, void *arg)
{
    CollisionManager *manager = data_ov001_020a04bc;
    CollisionEntity *result = 0;
    int index;

    if (manager == 0) {
        return result;
    }
    for (index = manager->cursor; index < manager->count; index++) {
        s32 *cursor = &manager->cursor;
        CollisionEntity *entity = GetBoundedEntryField(index);
        CollisionVolume volume;
        BOOL hit;
        (*cursor)++;
        if (entity == 0) {
            continue;
        }
        if (entity->getVolume != 0) {
            hit = entity->getVolume(entity, &volume);
        } else {
            hit = FALSE;
        }
        if (!hit) {
            continue;
        }
        if (volume.maxX >= query->minX && volume.minX <= query->maxX
            && volume.maxZ >= query->minZ && volume.minZ <= query->maxZ
            && volume.maxY >= query->minY && volume.minY <= query->maxY) {
            hit = gCollisionTestPairDispatch[volume.shape][query->shape](&volume, query, arg, 0);
        } else {
            hit = FALSE;
        }
        if (hit) {
            result = entity;
            break;
        }
    }
    return result;
}


