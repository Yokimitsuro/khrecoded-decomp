#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct ObjectModel {
    u8 pad_00[0x88];
    u8 node[0xa4];
    VecFx32 position;
} ObjectModel;

typedef struct ObjectClass {
    u8 pad_00[0x14];
    u8 node[4];
} ObjectClass;

typedef struct FieldObject {
    u8 pad_00[0x8];
    ObjectModel *model;
    ObjectClass *objectClass;
    u8 pad_10[0x30];
    VecFx32 position;
    u8 pad_4c[0xc];
    s32 state;
    u8 pad_5c[0x8];
    s32 frame;
} FieldObject;

extern void MTX_Identity33_(MtxFx33 *mtx);
extern int *func_01ffb2f8(void *node, int track, int frame);
extern void func_01ffb12c(void *node);
extern s32 func_0202f4cc(void *animation, int index);
extern void func_01fff9a0(void *node, fx32 scale, MtxFx33 *rotation, int alpha, int flags);

void FieldObject_Draw(FieldObject *object)
{
    ObjectModel *model = object->model;
    MtxFx33 identity;
    MtxFx33 rotation;

    switch (object->state) {
    case 1:
        model->position = object->position;
        func_01ffb2f8(model->node, 0, object->frame);
        func_01ffb2f8(model->node, 2, object->frame);
        func_01ffb12c(model->node);
        if (object->frame < func_0202f4cc(object->objectClass->node, 2)) {
            func_01ffb12c(object->objectClass->node);
        }
        break;
    case 0: {
        void *node = object->objectClass->node;
        MTX_Identity33_(&identity);
        rotation = identity;
        func_01fff9a0(node, 0x1800, &rotation, 0x1f, 1);
        break;
    }
    case 2:
        break;
    }
}
