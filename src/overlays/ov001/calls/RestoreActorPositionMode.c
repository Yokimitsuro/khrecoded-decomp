#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SceneObject {
    u8 pad_00[0xa8];
    VecFx32 position;
} SceneObject;

typedef struct BodyOwnerInfo {
    u8 pad_00[0x83];
    u8 kind;
} BodyOwnerInfo;

typedef struct ActorBody {
    SceneObject *object;
    u8 pad_04[0x44];
    BodyOwnerInfo *ownerInfo;
} ActorBody;

typedef struct Actor {
    u8 pad_000[0xd18];
    ActorBody *body;
} Actor;

extern void func_02038e80(ActorBody *body, u32 arg);
extern void Obj_SetPosition(SceneObject *object, const VecFx32 *position);
extern s32 func_ov001_02063a38(void);
extern int LookupKindTableValue(int mode, u8 kind);

int RestoreActorPositionMode(Actor *actor)
{
    ActorBody *body;
    s32 mode;
    VecFx32 savedPosition;
    u32 result;
    SceneObject *object;

    body = actor->body;
    object = body->object;
    result = 0x10;
    savedPosition = object->position;
    func_02038e80(body, 0);
    Obj_SetPosition(actor->body->object, &savedPosition);
    mode = 0;
    if (actor->body->ownerInfo != NULL) {
        if (func_ov001_02063a38() == 7) {
            mode = 3;
        }
        result = LookupKindTableValue(mode, actor->body->ownerInfo->kind);
    }
    return result;
}
