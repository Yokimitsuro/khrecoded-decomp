#include "nitro/types.h"

typedef struct {
    u8 pad[0x80];
    u16 state;
} Actor;

extern Actor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void WriteSessionPackedBits(int bitIndex, u32 width, u32 value);

BOOL RecordPlayerStateFlags(void) {
    Actor *player = ActorRegistry_GetEntityByIndex(0);
    if ((s32)player->state < (s32)0x8000) {
        WriteSessionPackedBits(0x3629, 1, TRUE);
    } else {
        WriteSessionPackedBits(0x3629, 1, FALSE);
    }
    WriteSessionPackedBits(0x362a, 1, 1);
    return TRUE;
}
