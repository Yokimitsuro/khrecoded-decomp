#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorModel {
    u8 pad_000[0x14];
    u8 sceneNode[0xa4];
    VecFx32 position;
    u8 pad_0c4[0x1a8 - 0xc4];
    VecFx32 shadowPosition;
} ActorModel;

typedef struct FieldActor {
    u8 pad_00[0xc];
    ActorModel *model;
} FieldActor;

extern void func_01ffb12c(void *node);
extern void ShadowVolume_Draw(void *shadow);

void DrawActorWithShadow_02085b90(FieldActor *actor)
{
    VecFx32 shadowPos;

    func_01ffb12c(actor->model->sceneNode);
    shadowPos = actor->model->position;
    shadowPos.y -= 0x14cd;
    actor->model->shadowPosition = shadowPos;
    ShadowVolume_Draw(&actor->model->shadowPosition);
}
