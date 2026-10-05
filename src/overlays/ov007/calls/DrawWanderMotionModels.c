#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 active : 1;
    u8 airborne : 1;
    u8 flagsHigh : 6;
    u8 phase;
    u16 timer;
    VecFx32 origin;
    VecFx32 velocity;
    fx32 scale;
    int angle;
} LaunchMotion;

typedef struct {
    u8 pad_00[0x90];
    s8 alphaTable[1];
} WanderDef;

typedef struct {
    u8 pad_00[0x14];
    u16 nodeFlags;
    u8 pad_16[0x12];
    void *anim;
    u8 pad_2c[0x8];
    u8 renderObj[0x58];
    void *model;
    s16 rotY;
    u8 pad_92[0x26];
    VecFx32 position;
    VecFx32 scale;
} WanderRender;

typedef struct {
    u8 pad_00[0x8];
    WanderDef *def;
    WanderRender *render;
    u8 pad_10[0x54];
    LaunchMotion motion[2];
    u8 pad_ac[0x7];
    s8 alphaIndex;
} WanderObject;

extern s8 FindActorRewardValue(VecFx32 *position);
extern void NNS_G3dRenderObjRemoveAnmObj(void *renderObj, void *anim);
extern void NNS_G3dRenderObjAddAnmObj(void *renderObj, void *anim);
extern int NNS_G3dMdlGetMdlAlpha(void *model, int material);
extern int NNS_G3dMdlGetMdlPolygonID(void *model, int material);
extern void NNS_G3dMdlSetMdlAlphaAll(void *model, int alpha);
extern void NNS_G3dMdlSetMdlPolygonIDAll(void *model, int polygonId);
extern void func_01ffb12c(void *node);

void DrawWanderMotionModels(WanderObject *object)
{
    WanderRender *render = object->render;
    WanderDef *def = object->def;
    int i;
    LaunchMotion *motion;
    int alpha;
    int polygonId;

    for (i = 1; i >= 0; i--) {
        motion = &object->motion[i];

        if (!motion->airborne) {
            continue;
        }
        if (object->alphaIndex < 0) {
            VecFx32 probe = motion->origin;
            probe.y += 0x800;
            object->alphaIndex = FindActorRewardValue(&probe);
        }
        render->position = motion->origin;
        render->scale.x = render->scale.y = render->scale.z = motion->scale;
        render->rotY = motion->angle;
        render->nodeFlags |= 0x20;
        if (object->alphaIndex >= 0 && def->alphaTable[object->alphaIndex] < 0x1f) {
            if (render->anim != NULL) {
                NNS_G3dRenderObjRemoveAnmObj(render->renderObj, render->anim);
            }
            alpha = NNS_G3dMdlGetMdlAlpha(render->model, 0);
            polygonId = NNS_G3dMdlGetMdlPolygonID(render->model, 0);
            NNS_G3dMdlSetMdlAlphaAll(render->model, def->alphaTable[object->alphaIndex]);
            NNS_G3dMdlSetMdlPolygonIDAll(render->model, 8);
        }
        func_01ffb12c(&render->nodeFlags);
        if (object->alphaIndex >= 0 && def->alphaTable[object->alphaIndex] < 0x1f) {
            NNS_G3dMdlSetMdlAlphaAll(render->model, alpha);
            NNS_G3dMdlSetMdlPolygonIDAll(render->model, polygonId);
            if (render->anim != NULL) {
                NNS_G3dRenderObjAddAnmObj(render->renderObj, render->anim);
            }
        }
    }
}
