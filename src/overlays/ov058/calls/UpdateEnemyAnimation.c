#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x230];
    int model;
    u8 pad_234[0x760 - 0x234];
    int frame;
    u8 pad_764[4];
    int eventFlag;
    u8 pad_76c[0x9b4 - 0x76c];
    u8 pool;
    u8 pad_9b5[0x9ec - 0x9b5];
    int delta;
    u8 pad_9f0[0x9fc - 0x9f0];
    u16 angleOffset;
    u8 pad_9fe[0xb68 - 0x9fe];
    u8 parts[2][0x230];
    u8 pad_fc8[0x1070 - 0xfc8];
    u8 members[0x94];
    int trackedMember;
} AnimActor;

extern u16 AdvanceAnimationTracks(int state, int delta);
extern int Anim_GetFrame(int state, int track);
extern u16 GetLinkedAngleOffset(AnimActor *actor);
extern void AdvanceObjectAnimationTracks(void *object, int delta);
extern void InvokeMemberUpdateCallbacks(void *container, int argument);
extern void func_ov021_020a8b08(int pool, int argument);
extern int func_ov001_0206db8c(int index);
extern BOOL IsGroupMemberActive(int groupId, int index);

void UpdateEnemyAnimation(AnimActor *actor, int argument)
{
    s16 events = AdvanceAnimationTracks(actor->model + 4, actor->delta);
    int i;
    int member;

    actor->frame = Anim_GetFrame(actor->model + 4, 0);
    actor->angleOffset = GetLinkedAngleOffset(actor);
    actor->eventFlag = 0;
    if (events & 1) {
        actor->eventFlag = 1;
    }
    for (i = 0; i < 2; i++) {
        AdvanceObjectAnimationTracks(actor->parts[i], actor->delta);
    }
    InvokeMemberUpdateCallbacks(actor->members, argument);
    func_ov021_020a8b08(actor->pool, argument);
    member = actor->trackedMember;
    if (member >= 0) {
        if (!IsGroupMemberActive(func_ov001_0206db8c(0), member)) {
            actor->trackedMember = -1;
        }
    }
}
