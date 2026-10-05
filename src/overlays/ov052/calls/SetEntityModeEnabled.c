#include "nitro/types.h"

typedef struct Entity Entity;

typedef void (*EntityNotifyFunc)(Entity *entity, int arg1, int arg2);
typedef void (*EntityModeFunc)(Entity *entity, int mode);

struct Entity {
    u8 pad_000[0x1F8];
    EntityNotifyFunc notifyCallback;
    u8 pad_1FC[0x6AC - 0x1FC];
    s32 unk_6AC;
    s32 unk_6B0;
    s32 unk_6B4;
    u8 pad_6B8[0x75C - 0x6B8];
    s32 unk_75C;
    u8 pad_760[0x9AC - 0x760];
    u64 stateFlags;
    u8 pad_9B4[0x9C8 - 0x9B4];
    s32 unk_9C8;
    s32 unk_9CC;
    s32 unk_9D0;
    s32 unk_9D4;
    s32 unk_9D8;
    s32 unk_9DC;
    s32 unk_9E0;
    s32 unk_9E4;
    s32 unk_9E8;
    u8 pad_9EC[0xA10 - 0x9EC];
    s32 unk_A10;
    u8 pad_A14[0x1030 - 0xA14];
    s32 unk_1030;
    s8 unk_1034;
    u8 pad_1035;
    s8 unk_1036;
    u8 pad_1037[0x1048 - 0x1037];
    u8 unk_1048;
    u8 pad_1049[0x1070 - 0x1049];
    u8 unk_1070[0x10EC - 0x1070];
    EntityModeFunc modeCallback;
    u8 pad_10F0[0x1108 - 0x10F0];
    u8 unk_1108[4];
};

extern BOOL func_ov001_02072040(void);
extern void RunHudExitCallback(void);
extern void ClearFlagAndField0x144(void *obj);
extern void InvokeMemberCleanupCallbacks(void *obj);
extern void SetActorPaused(Entity *entity, int arg);

void SetEntityModeEnabled(Entity *entity, int mode, int enable)
{
    switch (mode) {
    case 0:
        if (enable) {
            entity->stateFlags |= 0x20;
            if (func_ov001_02072040()) {
                RunHudExitCallback();
            }
            entity->unk_9C8 = 0;
            entity->unk_9D0 = 0;
        } else {
            entity->unk_9D0 = 0;
            entity->unk_9CC = 0;
            entity->unk_9C8 = 0;
            entity->unk_9DC = 0;
            entity->unk_9D8 = 0;
            entity->unk_9D4 = 0;
            entity->stateFlags &= ~(u64)0x20;
            entity->unk_1034 = -1;
            entity->unk_1036 = -1;
        }
        entity->stateFlags &= ~(u64)0x1A;
        entity->unk_1030 = 0;
        ClearFlagAndField0x144(entity->unk_1108);
        entity->unk_1048 = 0;
        entity->unk_A10 = 0;
        entity->unk_9E8 = 0;
        entity->unk_9E4 = 0;
        entity->unk_9E0 = 0;
        break;
    case 3:
        if (enable) {
            entity->stateFlags |= 0x80000000;
        } else {
            entity->stateFlags &= ~(u64)0x80000000;
        }
        break;
    case 1:
        entity->unk_6B4 = 0;
        entity->unk_6B0 = 0;
        entity->unk_6AC = 0;
        if (enable) {
            entity->stateFlags |= 0x100000000ULL;
        } else {
            entity->stateFlags &= ~0x100000000ULL;
        }
        break;
    case 2:
        entity->unk_9D0 = 0;
        entity->unk_9CC = 0;
        entity->unk_9C8 = 0;
        entity->unk_9DC = 0;
        entity->unk_9D8 = 0;
        entity->unk_9D4 = 0;
        entity->unk_9E8 = 0;
        entity->unk_9E4 = 0;
        entity->unk_9E0 = 0;
        if (enable) {
            entity->modeCallback(entity, 1);
            if ((entity->stateFlags & 0x40000000) == 0) {
                entity->unk_75C = -1;
                if (entity->notifyCallback != NULL) {
                    entity->notifyCallback(entity, 0, 0);
                }
            }
            SetActorPaused(entity, 0);
            entity->stateFlags = (u32)entity->stateFlags & 0x40000460;
            entity->unk_A10 = 0;
            entity->stateFlags |= 0x8000000;
            entity->stateFlags &= ~(u64)0x80000000;
        } else {
            InvokeMemberCleanupCallbacks(entity->unk_1070);
        }
        break;
    }
}
