#include "nitro/types.h"

extern void *FindRecordById_0209c304(u16 groupId);
extern void *GetLinkedStageActor(void *node);
extern void func_ov001_020917b4(void *node, u32 message);

void NotifyActorGroupMembers(u8 *actor, u32 message)
{
    void *node;

    for (node = FindRecordById_0209c304(*(u16 *)(actor + 0x10)); node != 0; node = GetLinkedStageActor(node)) {
        func_ov001_020917b4(node, message);
    }
}
