#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x12];
    u16 stageObjectId;
} StageInfo;

typedef struct {
    u8 pad_00[0x2c0];
    VecFx32 position;
} PlayerActor;

typedef struct {
    StageInfo *stage;
    u32 pad_04;
    PlayerActor *player;
} FieldContext;

typedef struct {
    u8 pad_00[8];
    VecFx32 center;
    fx32 radius;
} SpawnArea;

typedef struct {
    u8 pad_00[0x34];
    VecFx32 position;
} SpawnTarget;

extern FieldContext data_ov021_020b56c4;
extern const s16 data_02053580[];

extern u16 *func_ov001_0209c0ec(u32 id);
extern SpawnArea *func_ov001_0209c334(u32 index);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern s32 func_ov001_02063a38(void);
extern u32 random_next_scaled(u32 upperBound);
extern u16 FX_Atan2Idx(int y, int x);
extern int nextRandom12(void);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void func_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

s32 PickSpawnPointNearPlayer(SpawnTarget *target)
{
    StageInfo *stage = data_ov021_020b56c4.stage;
    PlayerActor *player = data_ov021_020b56c4.player;
    SpawnArea *area;
    fx32 distance;
    VecFx32 normal;
    VecFx32 direction;
    VecFx32 offset;

    if (stage == NULL) {
        return 0;
    }
    if (player == NULL) {
        return 0;
    }
    area = func_ov001_0209c334(*func_ov001_0209c0ec(stage->stageObjectId));
    func_01ff9e3c(&player->position, &area->center, &offset);
    distance = VEC_Mag(&offset);
    if (func_ov001_02063a38() != 4) {
        int angle;
        int index;
        if (distance < 0x19a) {
            angle = random_next_scaled(0x10000);
        } else {
            int heading;
            VEC_Normalize(&offset, &normal);
            heading = FX_Atan2Idx(-normal.x, -normal.z);
            angle = random_next_scaled(0x4000) - 0x4000;
            angle = (heading + angle + 0xffff) % 0xffff;
        }
        index = angle >> 4;
        direction.x = data_02053580[index];
        direction.y = 0;
        direction.z = data_02053580[(0x400 - index) & 0xfff];
        func_01ffa09c((area->radius >> 1) + FX_Mul(area->radius >> 1, nextRandom12()), &direction, &area->center, &target->position);
    } else {
        target->position = area->center;
        target->position.z = 0;
        if (distance < 0x19a) {
            if (random_next_scaled(2) == 0) {
                target->position.x = area->center.x + area->radius;
            } else {
                target->position.x = area->center.x - area->radius;
            }
        } else {
            target->position = area->center;
            if (offset.x < 0) {
                target->position.x = area->center.x + area->radius;
            } else {
                target->position.x = area->center.x - area->radius;
            }
        }
    }
    return 0;
}
