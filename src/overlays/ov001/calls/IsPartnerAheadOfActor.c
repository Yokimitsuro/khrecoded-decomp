#include "nitro/types.h"

extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern BOOL func_ov001_020645c8(u32 bitOffset);
extern u32 ActorSlot_GetByIndex(u32 actorId);
extern u32 ActorRegistry_GetEntityByIndex(u32 actorId);
extern void func_ov001_02088ab0(u32 source, int *outX, int *outY);

BOOL IsPartnerAheadOfActor(int actorId)
{
    u32 partner = ReadSessionPackedBits(0x3615, 8);
    BOOL locked = func_ov001_020645c8(0x3638);
    BOOL result;
    int leaderX;
    int leaderY;
    int partnerX;
    int partnerY;

    if ((actorId == -1 && partner != 0) || locked) {
        result = FALSE;
    } else if (actorId == -1 || partner == 0 || ActorSlot_GetByIndex((u16)actorId) == 0) {
        result = TRUE;
    } else {
        result = FALSE;
        func_ov001_02088ab0(ActorRegistry_GetEntityByIndex(0) + 0xa8, &leaderX, &leaderY);
        func_ov001_02088ab0(ActorRegistry_GetEntityByIndex((u16)partner) + 0xa8, &partnerX, &partnerY);
        if (actorId == 0) {
            if (leaderY > partnerY) {
                result = TRUE;
            }
        } else if (partnerY > leaderY) {
            result = TRUE;
        }
    }
    return result;
}
