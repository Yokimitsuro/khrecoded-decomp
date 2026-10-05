#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_000[0x11c];
    u8 surface[0x170];
    u16 stageBits : 11;
    u16 stageEntry : 3;
    u16 stageUnused : 2;
    u8 pad_28e[0x32];
    VecFx32 position;
} PlayerActor;

typedef struct {
    u8 pad_00[8];
    PlayerActor *player;
} FieldContext;

typedef struct {
    u8 pad_00[0x34];
    VecFx32 position;
} ScriptObject;

typedef struct {
    u8 pad_00[8];
    s16 distance[4];
    s16 angle[4];
    s16 flags[4];
} PlaceCommand;

extern FieldContext data_ov021_020b56c4;
extern const s16 data_02053580[];

extern s16 *ResolveTaggedValueRef(ScriptObject *obj, s16 *value);
extern s32 TaggedValueToFixed(s16 *tagged);
extern s32 TaggedValueToInt(s16 *tagged);
extern void func_ov001_02091c5c(PlayerActor *actor, VecFx32 *out);
extern u32 GetStageEntryParam(u32 id);
extern fx32 Surface_GetKindValue(void *surface);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void GetStageEntryPosition(u32 id, VecFx32 *outPosition);
extern void MTX_Identity33_(MtxFx33 *mtx);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void func_01ff9404(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern BOOL func_ov021_020afd48(VecFx32 *from, VecFx32 *to, VecFx32 *hitNormal, VecFx32 *hitPoint, int mode);

s32 ScriptOp_PlaceAroundPlayer(ScriptObject *obj, PlaceCommand *cmd)
{
    s16 *distanceRef = ResolveTaggedValueRef(obj, cmd->distance);
    s16 *angleRef = ResolveTaggedValueRef(obj, cmd->angle);
    s16 *flagsRef = ResolveTaggedValueRef(obj, cmd->flags);
    PlayerActor *player = data_ov021_020b56c4.player;
    fx32 distance;
    fx32 degrees;
    u32 flags;
    int angle;
    fx32 minDistance;
    VecFx32 base;
    VecFx32 direction;
    VecFx32 hitNormal;
    VecFx32 hitPoint;
    MtxFx33 rotation;

    func_ov001_02091c5c(player, &base);
    distance = TaggedValueToFixed(distanceRef);
    degrees = TaggedValueToFixed(angleRef);
    flags = TaggedValueToInt(flagsRef);
    angle = (u16)(((s64)degrees * 0xb60b60b60bLL + 0x80000000000LL) >> 44);
    minDistance = GetStageEntryParam(player->stageEntry) + Surface_GetKindValue(player->surface);
    if (distance < minDistance) {
        distance = minDistance;
    }
    if (flags & 1) {
        VEC_Subtract(&player->position, &base, &direction);
        direction.y = 0;
        func_01ffaff4(&direction, &direction);
    } else {
        GetStageEntryPosition(player->stageEntry, &direction);
    }
    if (flags & 2) {
        flags |= 4;
    }
    if (flags & 4) {
        MTX_Identity33_(&rotation);
        MTX_RotY33_(&rotation, data_02053580[angle >> 4], data_02053580[(0x400 - (angle >> 4)) & 0xfff]);
        func_01ff9404(&direction, &rotation, &direction);
        VEC_MultAdd(distance, &direction, &base, &obj->position);
        if (func_ov021_020afd48(&player->position, &obj->position, &hitNormal, &hitPoint, 1)) {
            if (flags & 2) {
                obj->position = player->position;
            } else {
                obj->position = hitPoint;
            }
        }
    }
    return 0;
}
