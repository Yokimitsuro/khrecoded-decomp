#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    VecFx32 *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    u8 data[0x28];
} SegmentStorage;

typedef struct {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct {
    u32 words[0x18];
} CollisionQuery;

typedef struct {
    u16 id;
    u16 isPartner : 1;
    u16 isLocked : 1;
    u16 unk_02_2 : 14;
    u16 kind;
    u16 pad_06;
    VecFx32 position;
    s32 width;
    s32 height;
    s32 displayWidth;
    s32 displayHeight;
} EventTargetInfo;

typedef struct {
    s32 id;
    s32 count;
    s32 param;
    VecFx32 start;
    VecFx32 end;
    s32 result;
} PathSegment;

typedef struct {
    s32 power;
    u8 pad_04[0xc];
    u8 reaction;
    u8 pad_11[0x13];
    u16 pathHit : 1;
    u16 unk_24_1 : 6;
    u16 sweep : 1;
    u16 unk_24_8 : 8;
    u8 pad_26[2];
} HitOptions;

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[8];
    void *attach;
    u8 pad_1c[8];
    u8 hidden;
    u8 layer;
    u16 flags;
    u16 soundId;
    u16 delay;
} MarkerRequest;

typedef struct {
    u8 pad_00[2];
    s16 paused;
} GroupMember;

typedef struct {
    u8 pad_000[0x230];
    void *collider;
    u8 pad_234[0x6cc - 0x234];
    u8 attachPoint[0x9b4 - 0x6cc];
    u8 player;
} Actor;

typedef struct {
    u8 pad_00[0x14];
    int player;
} SceneOwner;

typedef struct {
    u8 pad_00[8];
    int sound;
    u8 pad_0c[0x38];
    u8 phase;
    u8 pad_45[3];
    fx32 elapsed;
    u8 burstCount;
    u8 pad_4d[3];
    VecFx32 origin;
    s16 loopEmitter;
    s16 chargeEmitter;
    s16 impactEmitter;
    s16 sparkEmitter;
    int loopHandle;
} SceneObject;

extern const VecFx32 data_ov064_020d8844;
extern const VecFx32 data_ov064_020d8850;

extern Actor *GetBoundedEntryField(int index);
extern GroupMember *GetGroupMemberData(int groupId, int index);
extern int Anim_GetFrame(void *anim, int track);
extern fx32 func_0202f4cc(void *anim, int track);
extern void ResetAnimationTrackState(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern void StopAndClearSoundEmitter(int emitter, int handle);
extern u16 GetLinkedAngleOffset(Actor *actor);
extern VecFx32 *func_ov052_020ceb74(Actor *actor);
extern void RotateOffsetAroundY(VecFx32 *out, const VecFx32 *origin, u16 angle, const VecFx32 *offset);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern CollisionShape func_0203ade0(SegmentStorage *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern void *SweepWorldCollision(CollisionQuery *query);
extern s32 ForwardToActiveServiceWithResult(void);
extern s32 func_ov001_0208796c(s32 id);
extern int IsStageEventReady(u32 id);
extern BOOL func_ov001_02087988(u32 id, EventTargetInfo *out);
extern void ZeroBytes0x28(void *obj);
extern void InitPathSegment(PathSegment *segment, s32 id, s32 count, s32 param, const VecFx32 *start, const VecFx32 *end);
extern void func_ov021_020ac35c(HitOptions *options, PathSegment *segment);
extern void func_ov001_0206e6f4(int level);
extern void func_ov001_0206e750(int level);
extern void func_ov001_0206e7c0(void);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern u32 func_0202a9e4(u32 range);

void UpdateOv064BossSequence(SceneOwner *owner, SceneObject *obj, fx32 delta)
{
    CollisionQuery sweep;
    QueryWorkspace workspace;
    CollisionQuery query;
    MarkerRequest request;
    VecFx32 chargeOffset;
    VecFx32 burstOffset;
    SegmentStorage segment;
    CollisionShape shape;
    VecFx32 start;
    VecFx32 end;
    EventTargetInfo info;
    VecFx32 diff;
    HitOptions options;
    PathSegment path;
    VecFx32 scatter;
    VecFx32 rotated;
    VecFx32 burstPos;
    CollisionShape shapeResult;
    VecFx32 offset;
    VecFx32 axis;
    Actor *actor;
    GroupMember *member;
    int frame;
    s32 event;
    fx32 level;

    actor = GetBoundedEntryField(owner->player);
    if (obj->phase != 0) {
        obj->elapsed += delta;
    }
    if (obj->loopHandle >= 0) {
        member = GetGroupMemberData(obj->loopEmitter, obj->loopHandle);
        if (member->paused == 0) {
            frame = Anim_GetFrame(member, 0);
            if (delta + frame >= func_0202f4cc(member, 0)) {
                ResetAnimationTrackState(&request);
                request.id = actor->player;
                request.layer = 2;
                request.flags = 6;
                request.hidden = 1;
                request.attach = actor->attachPoint;
                StopAndClearSoundEmitter(obj->loopEmitter, obj->loopHandle);
                obj->loopHandle = func_ov021_020a8cc0(&request, obj->loopEmitter);
            }
        }
    }
    switch (obj->phase) {
    case 1:
        if (obj->loopHandle != -1) {
            StopAndClearSoundEmitter(obj->loopEmitter, obj->loopHandle);
            obj->loopHandle = -1;
        }
        chargeOffset = data_ov064_020d8850;
        ResetAnimationTrackState(&request);
        request.id = actor->player;
        request.layer = 0;
        request.hidden = 0;
        RotateOffsetAroundY(&rotated, func_ov052_020ceb74(actor), GetLinkedAngleOffset(actor) + 0x8000, &chargeOffset);
        request.position = rotated;
        request.soundId = obj->sound;
        request.delay = 1;
        func_ov021_020a8cc0(&request, obj->chargeEmitter);
        obj->elapsed = 0;
        obj->phase = 2;
        return;
    case 2:
        if (obj->elapsed > 0x6000) {
            StopAndClearSoundEmitter(obj->chargeEmitter, 0);
            burstOffset = data_ov064_020d8844;
            RotateOffsetAroundY(&burstPos, func_ov052_020ceb74(actor), GetLinkedAngleOffset(actor) + 0x8000, &burstOffset);
            obj->origin = burstPos;
            ResetAnimationTrackState(&request);
            request.id = actor->player;
            request.layer = 0;
            request.hidden = 1;
            request.position = obj->origin;
            request.soundId = obj->sound;
            request.delay = 2;
            func_ov021_020a8cc0(&request, obj->chargeEmitter);
            end = obj->origin;
            start = end;
            end.y -= 0x1e000;
            VEC_Subtract(&end, &start, &offset);
            axis = offset;
            shapeResult = func_0203ade0(&segment, &start, &end, &axis, func_01ffaff4(&axis, &axis));
            shape = shapeResult;
            CollisionQuery_Init(&query, 0, actor->collider, 1, 1, 0, &shape, &workspace, NULL);
            sweep = query;
            if (SweepWorldCollision(&sweep) != NULL) {
                ResetAnimationTrackState(&request);
                request.id = actor->player;
                request.layer = 0;
                request.hidden = 0;
                request.position = shape.data[1];
                func_ov021_020a8cc0(&request, obj->impactEmitter);
            }
            for (event = ForwardToActiveServiceWithResult(); event != 0; event = func_ov001_0208796c(event)) {
                if (IsStageEventReady(event) && func_ov001_02087988(event, &info)
                    && (!info.isLocked || info.isPartner)) {
                    VEC_Subtract(&info.position, &obj->origin, &diff);
                    if (VEC_Mag(&diff) <= 0x28000) {
                        ZeroBytes0x28(&options);
                        options.power = 0x3400;
                        options.reaction = 1;
                        options.sweep = 1;
                        options.pathHit = 1;
                        InitPathSegment(&path, event, -1, owner->player, func_ov052_020ceb74(actor), NULL);
                        func_ov021_020ac35c(&options, &path);
                    }
                }
            }
            func_ov001_0206e6f4(0x10);
            obj->elapsed = 0;
            obj->phase = 3;
            obj->burstCount = 0;
            return;
        }
        break;
    case 3:
        level = FX_Mul(0x10000, FX_Div(obj->elapsed, 0x32000));
        func_ov001_0206e750((s8)(0x10 - ((level + 0xfff) >> 12)));
        if (obj->burstCount < 10) {
            if (obj->elapsed % 0x2000 == 0) {
                ResetAnimationTrackState(&request);
                request.id = actor->player;
                request.layer = 0;
                request.hidden = 0;
                scatter.x = func_0202a9e4(0xa00) - 0x500;
                scatter.y = func_0202a9e4(0x300) - 0x200;
                scatter.z = func_0202a9e4(0xa00) - 0x500;
                if (scatter.x != 0 || scatter.y != 0 || scatter.z != 0) {
                    VEC_Normalize(&scatter, &scatter);
                }
                VEC_MultAdd(func_0202a9e4(0x2000) + 0x2000, &scatter, &obj->origin, &request.position);
                request.position.y += 1.0f;
                func_ov021_020a8cc0(&request, obj->sparkEmitter);
                obj->burstCount++;
                return;
            }
        } else if (obj->elapsed > 0x32000) {
            func_ov001_0206e7c0();
            obj->phase = 0;
        }
        break;
    }
}
