#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CollBox {
    fx32 maxX;
    fx32 maxY;
    fx32 maxZ;
    fx32 minX;
    fx32 minY;
    fx32 minZ;
} CollBox;

typedef struct CollShape {
    void *data;
    CollBox box;
    s32 kind;
} CollShape;

typedef struct CollSweep {
    CollShape shape;
    VecFx32 delta;
    CollBox sweepBox;
} CollSweep;

typedef struct CollHit {
    s32 unk_00;
    VecFx32 normal;
    fx32 time;
    s32 unk_14;
} CollHit;

typedef struct MeshFace {
    fx32 minX;
    fx32 minZ;
    fx32 maxX;
    fx32 maxZ;
    u16 flags;
    u8 pad_12[0x76];
} MeshFace;

typedef struct CollObject {
    u8 pad_00[4];
    struct CollObject *next;
    u8 pad_08[6];
    u16 groupMask;
    u8 pad_10[4];
    s32 ownerId;
} CollObject;

typedef struct CollMover {
    u32 flags;
    MeshFace *faces;
    u8 pad_08[0x30];
    CollSweep sweep;
    u8 hasSweep;
    u8 pad_7d[0xf];
    s32 ownerId;
    u16 ignoreMask;
} CollMover;

typedef struct QuadNode {
    u16 flags;
    s16 firstFace;
    u8 pad_04[4];
    CollObject *objects;
    u8 pad_0c[4];
    struct QuadNode *children[4];
} QuadNode;

typedef struct QuadCell {
    u16 quadrant;
    u8 pad_02[2];
    fx32 centerX;
    fx32 centerZ;
    fx32 size;
} QuadCell;

typedef struct MotionQueue {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0c;
    CollObject *hitObject;
} MotionQueue;

extern u8 data_027e0164[];
extern MotionQueue data_027e0134;
extern QuadCell *data_027e00b0;

extern fx32 TestMoverAgainstFace(MeshFace *face, CollMover *mover, CollHit *hit, CollBox *box);
extern fx32 TestMoverAgainstTarget(CollObject *object, CollMover *mover);
extern void InitPlaneContact(CollObject *object, CollMover *mover, void *out);

void *FindQuadTreeContact(QuadNode *node, CollMover *mover)
{
    CollHit hit;
    void *best = NULL;
    CollBox *box;

    if (mover->hasSweep) {
        box = &mover->sweep.sweepBox;
    } else {
        box = &mover->sweep.shape.box;
    }
    for (;;) {
        s16 index = node->firstFace;
        QuadCell *cell;
        u16 quadrant;
        fx32 quarter;
        fx32 centerX;
        QuadCell *next;

        if (index >= 0) {
            MeshFace *face = &mover->faces[index];
            do {
                if (!(face->flags & 0x4000)) {
                    fx32 time;
                    if (box->maxX < face->minX || box->minX > face->maxX || box->maxZ < face->minZ || box->minZ > face->maxZ) {
                        time = -FX32_ONE;
                    } else {
                        time = TestMoverAgainstFace(face, mover, &hit, box);
                    }
                    if (time >= 0 && hit.normal.y > 0) {
                        best = face;
                    }
                }
            } while (!((face++)->flags & 0x8000));
        }
        if (!(mover->flags & 1)) {
            CollObject *object = node->objects;
            CollObject *bestObject = NULL;
            s32 ownerId = mover->ownerId;
            u16 ignoreMask = mover->ignoreMask;

            for (; object != NULL; object = object->next) {
                if (object->ownerId != ownerId && !(object->groupMask & ignoreMask) && TestMoverAgainstTarget(object, mover) >= 0) {
                    bestObject = object;
                }
            }
            if (bestObject != NULL) {
                best = data_027e0164;
                InitPlaneContact(bestObject, mover, best);
                data_027e0134.hitObject = bestObject;
            }
        }
        cell = data_027e00b0;
        if (!(node->flags & 0xf00f)) {
            break;
        }
        next = cell + 1;
        quarter = cell->size / 4;
        centerX = cell->centerX;
        if (box->minX < centerX) {
            quadrant = (box->minZ < cell->centerZ) ? 0 : 2;
        } else {
            quadrant = (box->minZ < cell->centerZ) ? 1 : 3;
        }
        if (!((0x1001 << quadrant) & node->flags)) {
            break;
        }
        switch (quadrant) {
        case 0:
            next->centerX = centerX - quarter;
            next->centerZ = cell->centerZ - quarter;
            break;
        case 1:
            next->centerX = centerX + quarter;
            next->centerZ = cell->centerZ - quarter;
            break;
        case 2:
            next->centerX = centerX - quarter;
            next->centerZ = cell->centerZ + quarter;
            break;
        default:
            next->centerX = centerX + quarter;
            next->centerZ = cell->centerZ + quarter;
            break;
        }
        node = node->children[quadrant];
        next->quadrant = quadrant;
        data_027e00b0 = next;
    }
    return best;
}
