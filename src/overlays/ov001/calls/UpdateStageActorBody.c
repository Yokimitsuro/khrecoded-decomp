#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AnimResource {
    u8 pad_00[4];
    u16 frameCount;
} AnimResource;

typedef struct AnimTrack {
    fx32 frame;
    u8 pad_04[4];
    AnimResource *resource;
} AnimTrack;

typedef struct CollisionSegment {
    u8 pad_00[0xc];
    fx32 radius;
    u8 pad_10[0x14];
    fx32 halfHeight;
    fx32 height;
} CollisionSegment;

typedef struct CollisionShape {
    CollisionSegment *segment;
    u8 box[0x18];
    s32 shapeType;
} CollisionShape;

typedef struct ActorEntity {
    u32 flags;
    u16 animFlags;
    s16 animIds[5];
    AnimTrack *tracks[5];
    u8 pad_24[0x5c];
    u16 angle;
    u8 pad_82[0x26];
    VecFx32 position;
    u8 pad_b4[0x58];
    u8 collision[0x24];
    CollisionShape shape;
} ActorEntity;

typedef struct LinkedActor {
    u8 pad_00[0x88];
    fx32 height;
    fx32 radius;
} LinkedActor;

typedef struct StageSession {
    u32 flags;
} StageSession;

typedef struct StageActor {
    u8 pad_000[0x10];
    ActorEntity entity;
    u8 pad_160[0x122];
    u8 reverseMask;
    u8 visibleMask;
    u16 linkId;
    u8 pad_286[2];
    u16 flags_0 : 12;
    u16 frozen : 1;
    u16 flags_13 : 3;
    u8 pad_28a[0x2a];
    fx32 collisionLift;
    u8 pad_2b8[8];
    VecFx32 position;
    u8 pad_2cc[0x1a];
    u16 angle;
    u16 targetAngle;
    u8 pad_2ea[0x32];
    fx32 scale;
} StageActor;

extern fx32 ApplyActorScaleFactors(StageActor *actor);
extern u32 func_ov001_0209c5ac(u32 mask);
extern void Obj_SetPosition(ActorEntity *entity, const VecFx32 *position);
extern void ApplyActorDisplayParams(StageActor *actor);
extern LinkedActor *GetStageLinkedActor(u32 id);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void UpdateSegmentEndpoint(CollisionSegment *segment);
extern void (*gCollisionBoundsDispatch[])(CollisionShape *shape, void *box);
extern void UpdateModelScaleTween(StageActor *actor, fx32 step);
extern void AdvanceAlphaFade(StageActor *actor, fx32 step);
extern StageSession *func_ov001_0209c3e8(void);
extern void *GetActorRegistry(void);
extern void SetCollisionObjectPosition(void *object, const VecFx32 *position);
extern u32 Obj_UpdateQuadTreeLink(void *world, ActorEntity *entity, fx32 step);

void UpdateStageActorBody(StageActor *actor)
{
    ActorEntity *entity = &actor->entity;
    fx32 step = ApplyActorScaleFactors(actor);
    CollisionShape *shape;
    LinkedActor *linked;
    void *world;
    StageSession *session;
    u32 visibleMask;
    u16 i;
    u32 bit;
    AnimTrack *track;
    VecFx32 lifted;

    if (func_ov001_0209c5ac(0x30) == 0) {
        Obj_SetPosition(entity, &actor->position);
        ApplyActorDisplayParams(actor);
        entity = &actor->entity;
        if (actor->linkId != 0 && (linked = GetStageLinkedActor(actor->linkId)) != NULL) {
            shape = &entity->shape;
            switch (shape->shapeType) {
            case 3:
                if (shape->segment == NULL) {
                    break;
                }
                shape->segment->halfHeight = FX_Mul(linked->radius, actor->scale);
                shape->segment->height = FX_Mul(linked->height, actor->scale);
                UpdateSegmentEndpoint(shape->segment);
                gCollisionBoundsDispatch[shape->shapeType](shape, shape->box);
                break;
            case 4:
                if (shape->segment == NULL) {
                    break;
                }
                shape->segment->halfHeight = FX_Mul(linked->radius, actor->scale);
                shape->segment->height = FX_Mul(linked->height, actor->scale);
                UpdateSegmentEndpoint(shape->segment);
                gCollisionBoundsDispatch[shape->shapeType](shape, shape->box);
                break;
            case 0:
                if (shape->segment == NULL) {
                    break;
                }
                shape->segment->radius = FX_Mul(linked->height, actor->scale);
                gCollisionBoundsDispatch[shape->shapeType](shape, shape->box);
                break;
            }
        }
    } else {
        actor->position = entity->position;
        actor->angle = entity->angle;
        actor->targetAngle = entity->angle;
    }
    UpdateModelScaleTween(actor, step);
    AdvanceAlphaFade(actor, step);
    entity = &actor->entity;
    session = func_ov001_0209c3e8();
    visibleMask = 0;
    world = GetActorRegistry();
    if (world == NULL) {
        return;
    }
    if (actor->collisionLift != 0 && !(entity->flags & 0x10)) {
        lifted = entity->position;
        lifted.y += actor->collisionLift;
        SetCollisionObjectPosition(entity->collision, &lifted);
    }
    if (!actor->frozen) {
        visibleMask = Obj_UpdateQuadTreeLink(world, entity, step);
        actor->visibleMask = visibleMask;
    }
    if (session->flags & 1) {
        return;
    }
    for (i = 0; i < 5; i++) {
        if (entity->animIds[i] >= 0) {
            bit = 1 << i;
            if (visibleMask & bit) {
                track = entity->tracks[i];
                if (!(actor->reverseMask & bit)) {
                    track->frame = (track->resource->frameCount << 12) - step;
                } else {
                    track->frame = step;
                }
            }
        }
    }
}
