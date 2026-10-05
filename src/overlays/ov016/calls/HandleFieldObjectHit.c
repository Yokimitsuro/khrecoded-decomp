#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ImpactMessage {
    int type;
    VecFx32 direction;
    VecFx32 origin;
    int power;
    int unk_20;
    u8 pad_24[0xc];
    int unk_30;
    int unk_34;
} ImpactMessage;

typedef struct PushMessage {
    VecFx32 direction;
    int power;
    u8 pad_10[0x18];
    u16 flags;
    u8 pad_2a[0x4];
    u16 sourceId;
    u8 pad_30[0x4];
    VecFx32 origin;
    u8 pad_40[0x8];
} PushMessage;

typedef struct HitMessage {
    VecFx32 direction;
    u8 element;
    u8 unk_0d;
    u8 pad_0e[0x2];
    int damage;
    int unk_14;
    int unk_18;
} HitMessage;

typedef struct PlayerTarget {
    u8 pad_000[0xbc];
    VecFx32 position;
    u8 pad_0c8[0x1d4 - 0xc8];
    u16 *stats;
    u8 pad_1d8[0x208 - 0x1d8];
    void (*onImpact)(struct PlayerTarget *self, ImpactMessage *message);
} PlayerTarget;

typedef struct StageTarget {
    u8 pad_00[0x10];
    s16 actorIndex;
    u8 pad_12[0x74 - 0x12];
    int power;
} StageTarget;

typedef struct StageActor {
    u8 pad_000[0x2c0];
    VecFx32 position;
} StageActor;

typedef struct PropTarget {
    u8 pad_00[0x38];
    u8 id;
} PropTarget;

typedef struct UnitTarget {
    u8 pad_00[0x32];
    u8 id;
    u8 pad_33[0x38 - 0x33];
    VecFx32 position;
    u8 pad_44[0xbd - 0x44];
    u8 unk_bd_lo : 4;
    u8 mode : 4;
    u8 unk_be_lo : 4;
    u8 state : 4;
    u8 pad_bf[0xec - 0xbf];
    s16 *link;
} UnitTarget;

typedef struct BossInfo {
    u8 pad_00[0x1c];
    int power;
} BossInfo;

typedef struct HitOwner {
    u8 pad_000[0x194];
    u8 info[3];
} HitOwner;

typedef struct HitSource {
    u8 pad_00[0x14];
    HitOwner *owner;
} HitSource;

typedef struct HitEvent {
    HitSource *source;
    int kind;
} HitEvent;

typedef struct FieldObject {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[0x38 - 0x33];
    VecFx32 position;
    u8 pad_44[0xd8 - 0x44];
    u32 element : 8;
    u32 unk_d8_hi : 24;
} FieldObject;

extern BOOL func_ov001_02087674(HitEvent *event);
extern void *GetBoundedEntryField(int index);
extern void *GetStageEventRecord(int index);
extern PropTarget *func_ov001_0207f060(int group, int index);
extern UnitTarget *func_ov001_0208724c(int group, int index);
extern BOOL RecordVisitedEntry(FieldObject *object, int type, int id);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void func_01ff88c4(void *dst, u32 value, u32 size);
extern StageActor *GetStageActor(int index);
extern void func_ov001_0209591c(StageTarget *target, PushMessage *message);
extern void func_ov001_0207f874(PropTarget *target, HitMessage *message);
extern void func_ov001_02086408(UnitTarget *target, HitMessage *message);
extern BossInfo *func_ov032_020bbc80(UnitTarget *target);
extern void ApplyGroupLeaderHit(UnitTarget *target, PushMessage *message);

static inline VecFx32 VecNormalized(const VecFx32 *v)
{
    VecFx32 result;

    VEC_Normalize(v, &result);
    return result;
}

static inline VecFx32 VecScaled(VecFx32 v, fx32 scale)
{
    ScaleVecFx32InPlace(&v, scale);
    return v;
}

int HandleFieldObjectHit(HitEvent *event, int unused, FieldObject *object)
{
    PushMessage stagePush;
    PushMessage bossPush;
    ImpactMessage impact;
    VecFx32 playerDir;
    VecFx32 stageDir;
    HitMessage propHit;
    HitMessage unitHit;
    VecFx32 unitDir;
    VecFx32 bossDir;
    u8 *info;
    void *target;
    int id;
    int power;

    if (func_ov001_02087674(event)) {
        return 2;
    }
    if (event->kind == 4) {
        info = event->source->owner->info;
        target = NULL;
        id = 0;
        switch (info[0]) {
        case 0:
            target = GetBoundedEntryField(info[1]);
            id = info[1];
            break;
        case 1:
            if (info[1] == 1) {
                target = GetStageEventRecord(info[2]);
                id = info[2];
            }
            break;
        case 2:
            target = func_ov001_0207f060(info[1], info[2]);
            id = ((PropTarget *)target)->id;
            break;
        case 4:
            target = func_ov001_0208724c(info[1], info[2]);
            id = ((UnitTarget *)target)->id;
            break;
        }
        if (target != NULL) {
            if (RecordVisitedEntry(object, info[0], id)) {
                return 1;
            }
            switch (info[0]) {
            case 0: {
                PlayerTarget *player = target;

                power = (player->stats[2] << 13) / 10;
                VEC_Subtract(&player->position, &object->position, &playerDir);
                if (playerDir.x == 0 && playerDir.y == 0 && playerDir.z == 0) {
                    playerDir.x = 0x1000;
                }
                MI_CpuFill8(&impact, 0, sizeof(ImpactMessage));
                impact.type = 0x44;
                impact.power = power;
                impact.direction = VecScaled(VecNormalized(&playerDir), 0x1000);
                impact.origin = object->position;
                impact.unk_20 = 0;
                impact.unk_30 = 0;
                impact.unk_34 = 0;
                if (player->onImpact != NULL) {
                    player->onImpact(player, &impact);
                }
                break;
            }
            case 1: {
                StageActor *actor = GetStageActor(((StageTarget *)target)->actorIndex);

                power = ((StageTarget *)target)->power;
                func_01ff88c4(&stagePush, 0, sizeof(PushMessage));
                VEC_Subtract(&actor->position, &object->position, &stageDir);
                if (stageDir.x == 0 && stageDir.y == 0 && stageDir.z == 0) {
                    stageDir.x = 0x1000;
                }
                stagePush.flags |= 0x20;
                stagePush.sourceId = object->actorId;
                stagePush.power = power;
                stagePush.origin = object->position;
                stagePush.direction = VecScaled(VecNormalized(&stageDir), 0x800);
                func_ov001_0209591c(target, &stagePush);
                break;
            }
            case 2:
                propHit.element = 0xff;
                propHit.unk_0d = 0;
                propHit.damage = 0xa000;
                propHit.unk_14 = 0;
                propHit.unk_18 = 0;
                func_ov001_0207f874(target, &propHit);
                break;
            case 4: {
                UnitTarget *unit = target;
                BOOL hidden = TRUE;

                if (unit->state <= 3 && ((1 << unit->state) & 0xb)) {
                    hidden = FALSE;
                }
                if (!hidden) {
                    if (unit->mode < 5 || unit->link[2] != -1) {
                        VEC_Subtract(&unit->position, &object->position, &unitDir);
                        if (unitDir.x == 0 && unitDir.y == 0 && unitDir.z == 0) {
                            unitDir.x = 0x1000;
                        }
                        unitHit.element = object->element;
                        unitHit.unk_0d = 0;
                        unitHit.direction = VecScaled(VecNormalized(&unitDir), 0x800);
                        unitHit.damage = 1;
                        unitHit.unk_14 = 0;
                        unitHit.unk_18 = 0;
                        func_ov001_02086408(unit, &unitHit);
                    } else {
                        power = func_ov032_020bbc80(unit)->power * 3 / 10;
                        func_01ff88c4(&bossPush, 0, sizeof(PushMessage));
                        VEC_Subtract(&unit->position, &object->position, &bossDir);
                        if (bossDir.x == 0 && bossDir.y == 0 && bossDir.z == 0) {
                            bossDir.x = 0x1000;
                        }
                        func_01ff88c4(&bossPush, 0, sizeof(PushMessage));
                        bossPush.sourceId = object->actorId;
                        bossPush.flags |= 0x20;
                        bossPush.power = power;
                        bossPush.origin = object->position;
                        bossPush.direction = VecScaled(VecNormalized(&bossDir), 0x800);
                        ApplyGroupLeaderHit(unit, &bossPush);
                    }
                }
                break;
            }
            }
        }
    }
    return 1;
}
