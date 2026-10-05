#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct ModelNode {
    u16 flags;
    u8 pad_02[0x12];
    void *animObj;
    u8 pad_18[8];
    u8 renderObj[0x58];
    void *model;
    u8 pad_7c[0x28];
    VecFx32 translation;
} ModelNode;

typedef struct Owner {
    u8 pad_00[0x68];
    ModelNode *node;
} Owner;

typedef struct Entity {
    u32 flags;
    ModelNode node;
} Entity;

typedef struct Actor {
    u8 pad_00[4];
    Owner *owner;
    u8 pad_08[0x2a];
    u8 entityId;
    u8 pad_33[5];
    VecFx32 position;
    u8 pad_44[3];
    s8 shadowDisabled;
    ModelNode *modelNode;
    u8 pad_4c[3];
    u8 state : 3;
    u8 counter : 3;
    u8 pad_4f_6 : 2;
    s8 alpha;
    u8 pad_51[5];
    s16 angle;
    u8 pad_58[2];
    u16 flags;
} Actor;

extern u32 func_ov035_020bae94(void);
extern void func_ov001_02080a38(ModelNode *node, u32 value);
extern void func_01ffb12c(ModelNode *node);
extern Entity *ActorRegistry_GetEntityByIndex(u32 id);
extern void NNS_G3dRenderObjRemoveAnmObj(void *renderObj, void *animObj);
extern void NNS_G3dRenderObjAddAnmObj(void *renderObj, void *animObj);
extern u32 NNS_G3dMdlGetMdlAlpha(void *model, u32 materialIndex);
extern u32 NNS_G3dMdlGetMdlPolygonID(void *model, u32 materialIndex);
extern void NNS_G3dMdlSetMdlAlphaAll(void *model, int alpha);
extern void NNS_G3dMdlSetMdlPolygonIDAll(void *model, int polygonId);
extern void MTX_Identity33_(MtxFx33 *mtx);
extern void func_01fff9a0(ModelNode *node, fx32 size, MtxFx33 *rotation, int alpha, int mode);

void DrawActorModel(Actor *actor)
{
    Owner *owner = actor->owner;
    ModelNode *node;

    if (func_ov035_020bae94() != 0) {
        return;
    }
    if (actor->state == 2 || actor->alpha <= 0) {
        return;
    }
    if (actor->flags & 0x20) {
        owner->node->translation = actor->position;
        func_ov001_02080a38(owner->node, actor->angle << 12);
        func_01ffb12c(owner->node);
    }
    if (!(actor->flags & 0x40)) {
        return;
    }
    if ((actor->flags & 0x100) && !(actor->flags & 0x80)) {
        node = actor->modelNode;
    } else {
        node = &ActorRegistry_GetEntityByIndex(actor->entityId)->node;
    }
    if (actor->alpha < 31) {
        u32 savedAlpha;
        u32 savedPolygonId;
        if (node->animObj != NULL) {
            NNS_G3dRenderObjRemoveAnmObj(node->renderObj, node->animObj);
        }
        savedAlpha = NNS_G3dMdlGetMdlAlpha(node->model, 0);
        savedPolygonId = NNS_G3dMdlGetMdlPolygonID(node->model, 0);
        NNS_G3dMdlSetMdlAlphaAll(node->model, actor->alpha);
        NNS_G3dMdlSetMdlPolygonIDAll(node->model, 7);
        func_01ffb12c(node);
        NNS_G3dMdlSetMdlAlphaAll(node->model, savedAlpha);
        NNS_G3dMdlSetMdlPolygonIDAll(node->model, savedPolygonId);
        if (node->animObj != NULL) {
            NNS_G3dRenderObjAddAnmObj(node->renderObj, node->animObj);
        }
    } else if (actor->shadowDisabled == 0 && (node->flags & 2)) {
        MtxFx33 identity;
        MtxFx33 rotation;
        MTX_Identity33_(&identity);
        rotation = identity;
        func_01fff9a0(node, 0x1800, &rotation, 0x1f, 1);
    } else {
        func_01ffb12c(node);
    }
}
