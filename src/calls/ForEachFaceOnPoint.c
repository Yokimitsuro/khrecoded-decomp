#include "nitro/types.h"

typedef struct CollPoint {
    u8 pad_00[0x14];
} CollPoint;

typedef struct CollFace88 {
    u8 pad_00[0x80];
    u8 pointRefs[3];
    u8 pad_83[5];
} CollFace88;

typedef struct CollFace84 {
    u8 pad_00[0x80];
    u8 pointRefs[4];
} CollFace84;

typedef struct CollModel {
    u8 pad_00[0x7c];
    u16 floorCount;
    u16 wallCount;
    u16 ceilCount;
    u8 pad_82[0xa0 - 0x82];
    CollFace88 *floorFaces;
    CollFace84 *wallFaces;
    CollFace84 *ceilFaces;
    CollPoint *points;
} CollModel;

typedef void (*CollFaceCallback)(CollModel *model, void *face, void *arg);

void ForEachFaceOnPoint(CollModel *model, u8 kindMask, CollPoint *point, CollFaceCallback callback, void *arg)
{
    s32 index;
    s32 count;
    s32 ref;

    if (kindMask & 1) {
        count = model->floorCount;
        for (index = 0; index < count; index++) {
            CollFace88 *face = &model->floorFaces[index];
            for (ref = 1; ref <= 2; ref++) {
                u8 pointIndex = face->pointRefs[ref];
                if (pointIndex != 0xff && point == &model->points[pointIndex]) {
                    callback(model, face, arg);
                    break;
                }
            }
        }
    }
    if (kindMask & 2) {
        count = model->wallCount;
        for (index = 0; index < count; index++) {
            CollFace84 *face = &model->wallFaces[index];
            for (ref = 0; ref < 4; ref++) {
                u8 pointIndex = face->pointRefs[ref];
                if (pointIndex != 0xff && point == &model->points[pointIndex]) {
                    callback(model, face, arg);
                    break;
                }
            }
        }
    }
    if (kindMask & 4) {
        count = model->ceilCount;
        for (index = 0; index < count; index++) {
            CollFace84 *face = &model->ceilFaces[index];
            for (ref = 0; ref < 4; ref++) {
                u8 pointIndex = face->pointRefs[ref];
                if (pointIndex != 0xff && point == &model->points[pointIndex]) {
                    callback(model, face, arg);
                    break;
                }
            }
        }
    }
}
