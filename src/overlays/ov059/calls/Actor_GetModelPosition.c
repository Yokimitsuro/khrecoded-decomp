#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ModelInstance {
    u8 pad_00[0xa4];
    VecFx32 position;
} ModelInstance;

typedef struct ActorModel {
    u32 flags;
    ModelInstance instance;
} ActorModel;

typedef struct Actor {
    u8 pad_000[0x230];
    ActorModel *model;
} Actor;

VecFx32 *Actor_GetModelPosition(Actor *actor)
{
    return &actor->model->instance.position;
}
