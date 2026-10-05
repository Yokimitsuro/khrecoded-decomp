#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 type;
    VecFx32 velocity;
    VecFx32 position;
    u32 unk_1C;
    u32 unk_20;
    u8 pad_24[0x30 - 0x24];
    u32 unk_30;
    u32 unk_34;
} PushMessage;

typedef struct PlayerEntry PlayerEntry;

struct PlayerEntry {
    u8 pad_000[0x208];
    void (*onMessage)(PlayerEntry *player, PushMessage *message);
};

typedef struct {
    u8 pad_00[0x38];
    VecFx32 position;
    u8 pad_44[0xc0 - 0x44];
    u32 flags;
    u8 pad_c4[0xcc - 0xc4];
    VecFx32 velocity;
    s32 cooldown;
} FieldObject;

extern const VecFx32 data_0205344c;
extern PlayerEntry *func_ov001_0206db5c(int index);
extern void MI_CpuFill8(void *dst, u32 value, u32 size);
extern u32 SpawnSoundSlot(u32 owner, u32 kind, VecFx32 *position, u32 flags);
extern BOOL AreVecsWithinRange16(const VecFx32 *a, const VecFx32 *b);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void ScaleVecFx32InPlace(VecFx32 *v, fx32 scale);

void UpdateKickedFieldObject(FieldObject *obj)
{
    PushMessage message;
    VecFx32 velocity;
    PlayerEntry *player;
    fx32 speed;
    VecFx32 *current;

    if (obj->cooldown != 0) {
        obj->cooldown -= 0x89;
        if (obj->cooldown < 0) {
            obj->cooldown = 0;
        }
    }
    if (obj->flags & 0x10000) {
        player = func_ov001_0206db5c(0);
        if (obj->velocity.y <= 0 || obj->velocity.x != 0 || obj->velocity.z != 0) {
            velocity = obj->velocity;
            if (velocity.y < 0) {
                velocity.y /= 10;
            }
            MI_CpuFill8(&message, 0, sizeof(PushMessage));
            message.type = 0x42c;
            message.unk_1C = 0;
            message.velocity = velocity;
            message.position = obj->position;
            message.unk_20 = 0;
            message.unk_30 = 0;
            message.unk_34 = 0;
            if (player->onMessage != NULL) {
                player->onMessage(player, &message);
            }
        }
        SpawnSoundSlot(0, 0x49, &obj->position, 0);
        obj->flags &= ~0x10000;
        obj->flags |= 0x20000;
    }
    if (obj->flags & 0x20000) {
        if (!AreVecsWithinRange16(&obj->velocity, &data_0205344c)) {
            speed = VEC_Mag(&obj->velocity);
            current = &obj->velocity;
            VEC_Normalize(current, current);
            ScaleVecFx32InPlace(current, speed * 0x46 / 100);
            return;
        }
        obj->flags &= ~0x20000;
    }
}
