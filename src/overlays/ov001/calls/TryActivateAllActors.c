#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x30C];
    s32 sessionFlag;
    u8 pad_310[0x454];
    u8 pad_764[0x4];
    u32 field_768;
    u8 pad_76c[0x1F0];
    void *actorSlots[0x200];
    u8 partyMembers[3][0xF2C];
} ActorManager;

extern ActorManager *data_ov001_020a0500;
extern void RunEventScriptFrame(void);
extern void Actor_RestoreAnimState(void *actor, s32 flag);
extern void FinishEventCameraCut(void);

s32 TryActivateAllActors(void)
{
    s32 index;
    void *actor;

    RunEventScriptFrame();
    if (data_ov001_020a0500->field_768 == 0) {
        index = 0;
        do {
            actor = data_ov001_020a0500->actorSlots[index];
            if (actor != 0) {
                Actor_RestoreAnimState(actor, 1);
            }
            index = index + 1;
        } while (index < 0x200);
        index = 0;
        do {
            Actor_RestoreAnimState(data_ov001_020a0500->partyMembers[index], 1);
            index = index + 1;
        } while (index < 3);
        if (data_ov001_020a0500->sessionFlag != -1) {
            FinishEventCameraCut();
        }
        return 1;
    }
    return 0;
}
