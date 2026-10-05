#include "nitro/types.h"

typedef struct StageWalker {
    u8 pad_000[0x28a];
    u16 heading : 10;
    u16 turnState : 4;
    u16 headingFlags : 2;
    u16 stepKind : 3;
    u16 stepPhase : 4;
    u16 stepCount : 4;
    u16 stepFlags : 5;
} StageWalker;

void ClearWalkerStepState(StageWalker *walker)
{
    walker->stepCount = 0;
    walker->stepPhase = 0;
    walker->turnState = 0;
}
