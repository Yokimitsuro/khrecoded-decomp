#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CollBox {
    s32 maxX;
    s32 maxY;
    s32 maxZ;
    s32 minX;
    s32 minY;
    s32 minZ;
} CollBox;

typedef struct CollFace {
    s32 minX;
    s32 minZ;
    s32 maxX;
    s32 maxZ;
    u16 flags;
    u8 pad_12[0x88 - 0x12];
} CollFace;

typedef struct CollHit {
    s32 unk_00;
    VecFx32 normal;
    fx32 time;
    s32 unk_14;
} CollHit;

typedef struct CollTarget {
    u8 pad_00[4];
    struct CollTarget *next;
    u8 pad_08[6];
    u16 groupMask;
    u8 pad_10[4];
    u32 ownerId;
} CollTarget;

typedef struct CollNode {
    u16 flags;
    s16 faceIndex;
    u8 pad_04[4];
    CollTarget *targets;
    struct CollNode *parent;
    struct CollNode *children[4];
} CollNode;

typedef struct CollRegion {
    s32 centerX;
    s32 centerZ;
    s32 size;
} CollRegion;

typedef struct CollModel {
    u8 pad_00[0x84];
    CollRegion region;
    u8 pad_90[0xc];
    CollNode *root;
    CollFace *faces;
} CollModel;

typedef struct CollMover {
    u32 flags;
    CollFace *faces;
    u8 pad_08[0x34];
    CollBox box;
    s32 kind;
    u8 pad_58[0xc];
    CollBox sweepBox;
    u8 hasSweep;
    u8 pad_7d[3];
    VecFx32 direction;
    u32 ownerId;
    u16 groupMask;
} CollMover;

typedef struct CollTraversalFrame {
    s16 childIndex;
    u16 nodeFlags;
    s32 centerX;
    s32 centerZ;
    s32 size;
} CollTraversalFrame;

typedef struct CollHitRecord {
    CollModel *model;
    void *face;
    u8 pad_08[8];
    CollTarget *target;
} CollHitRecord;

extern void ResetCollTraversal(CollModel *model);
extern void *FindQuadTreeContact(CollNode *root, CollMover *mover);
extern s32 TestMoverAgainstFace(CollFace *face, CollMover *mover, CollHit *hit, CollBox *box);
extern s32 TestMoverAgainstTarget(CollTarget *target, CollMover *mover);
extern void InitPlaneContact(CollTarget *target, CollMover *mover, void *hitFace);
extern u8 data_027e0164[];
extern CollHitRecord data_027e0134;
extern CollTraversalFrame *data_027e00b0;
extern CollTraversalFrame data_027e00b4;

static inline s32 TestFace(CollFace *face, CollMover *mover, CollHit *hit, CollBox *box)
{
    if (box->maxX < face->minX || box->minX > face->maxX || box->maxZ < face->minZ || box->minZ > face->maxZ) {
        return -FX32_ONE;
    }
    return TestMoverAgainstFace(face, mover, hit, box);
}

BOOL TestMoverAgainstModelTree(CollMover *mover, CollModel *model)
{
    BOOL result = FALSE;
    BOOL inside;
    u32 ownerId;
    CollTarget *foundTarget;
    void *hitFace;
    s32 centerX;
    CollNode *node;
    CollBox *box;
    CollFace *face;
    CollTarget *target;
    u16 groupMask;
    u16 faceFlags;
    CollHit hit;
    CollTraversalFrame *nextFrame;
    CollTraversalFrame *parentFrame;
    CollTraversalFrame *frame;
    u16 nodeFlags;
    u16 siblingFlags;
    s32 quarter;
    s32 descentChild;
    s32 siblingChild;
    s16 previousChild;

    if (mover->hasSweep) {
        inside = mover->sweepBox.minX - model->region.centerX <= model->region.size && model->region.centerX - mover->sweepBox.maxX <= model->region.size
            && mover->sweepBox.minZ - model->region.centerZ <= model->region.size && model->region.centerZ - mover->sweepBox.maxZ <= model->region.size;
    } else {
        inside = mover->box.minX - model->region.centerX <= model->region.size && model->region.centerX - mover->box.maxX <= model->region.size
            && mover->box.minZ - model->region.centerZ <= model->region.size && model->region.centerZ - mover->box.maxZ <= model->region.size;
    }
    if (inside) {
        mover->faces = model->faces;
        ResetCollTraversal(model);
        if ((mover->direction.x | mover->direction.z) == 0 && mover->kind == 2) {
            hitFace = FindQuadTreeContact(model->root, mover);
        } else {
            node = model->root;
            hitFace = NULL;
            if (mover->hasSweep) {
                box = &mover->sweepBox;
            } else {
                box = &mover->box;
            }

        restart:
            if (node->faceIndex >= 0) {
                face = &mover->faces[node->faceIndex];
                do {
                    if ((face->flags & 0x4000) == 0) {
                        if (TestFace(face, mover, &hit, box) >= 0 && hit.normal.y > 0) {
                            hitFace = face;
                        }
                    }
                    faceFlags = face->flags;
                    face++;
                } while ((faceFlags & 0x8000) == 0);
            }

            if ((mover->flags & 1) == 0) {
                foundTarget = NULL;
                target = node->targets;
                ownerId = mover->ownerId;
                groupMask = mover->groupMask;
                while (target != NULL) {
                    if (target->ownerId != ownerId && (target->groupMask & groupMask) == 0 && TestMoverAgainstTarget(target, mover) >= 0) {
                        foundTarget = target;
                    }
                    target = target->next;
                }
                if (foundTarget != NULL) {
                    hitFace = data_027e0164;
                    InitPlaneContact(foundTarget, mover, hitFace);
                    data_027e0134.target = foundTarget;
                }
            }

            nodeFlags = node->flags;
            frame = data_027e00b0;
            if (nodeFlags & 0xf00f) {
                nextFrame = frame + 1;
                quarter = frame->size / 4;
                centerX = frame->centerX;
                if (box->maxX < centerX) {
                    nodeFlags &= 0x5555;
                } else if (box->minX > centerX) {
                    nodeFlags &= 0xaaaa;
                }
                if (box->maxZ < frame->centerZ) {
                    nodeFlags &= 0x3333;
                } else if (box->minZ > frame->centerZ) {
                    nodeFlags &= 0xcccc;
                }

                descentChild = 0xf;
                if (nodeFlags & 0x1001) {
                    nextFrame->centerX = centerX - quarter;
                    nextFrame->centerZ = frame->centerZ - quarter;
                    descentChild = 0;
                } else if (nodeFlags & 0x2002) {
                    nextFrame->centerX = centerX + quarter;
                    nextFrame->centerZ = frame->centerZ - quarter;
                    descentChild = 1;
                } else if (nodeFlags & 0x4004) {
                    nextFrame->centerX = centerX - quarter;
                    nextFrame->centerZ = frame->centerZ + quarter;
                    descentChild = 2;
                } else if (nodeFlags & 0x8008) {
                    nextFrame->centerX = centerX + quarter;
                    nextFrame->centerZ = frame->centerZ + quarter;
                    descentChild = 3;
                }

                if (descentChild != 0xf) {
                    node = node->children[descentChild];
                    nextFrame->childIndex = descentChild;
                    frame->nodeFlags = nodeFlags;
                    data_027e00b0 = nextFrame;
                    goto restart;
                }
            }

            while (frame != &data_027e00b4) {
                previousChild = frame->childIndex;
                if (previousChild == 3) {
                    frame--;
                    node = node->parent;
                    continue;
                }

                parentFrame = frame - 1;
                node = node->parent;
                siblingFlags = parentFrame->nodeFlags;
                quarter = parentFrame->size / 4;
                siblingChild = 0;

                switch (previousChild) {
                case 0:
                    if (siblingFlags & 0x2002) {
                        frame->centerX = parentFrame->centerX + quarter;
                        frame->centerZ = parentFrame->centerZ - quarter;
                        siblingChild = 1;
                        break;
                    }
                case 1:
                    if (siblingFlags & 0x4004) {
                        frame->centerX = parentFrame->centerX - quarter;
                        frame->centerZ = parentFrame->centerZ + quarter;
                        siblingChild = 2;
                        break;
                    }
                case 2:
                    if (siblingFlags & 0x8008) {
                        frame->centerX = parentFrame->centerX + quarter;
                        frame->centerZ = parentFrame->centerZ + quarter;
                        siblingChild = 3;
                    }
                    break;
                }

                if (siblingChild != 0) {
                    node = node->children[siblingChild];
                    frame->childIndex = siblingChild;
                    data_027e00b0 = frame;
                    goto restart;
                }
                frame--;
            }
        }

        if (hitFace != NULL) {
            data_027e0134.model = model;
            data_027e0134.face = hitFace;
            result = TRUE;
        }
    }
    return result;
}
