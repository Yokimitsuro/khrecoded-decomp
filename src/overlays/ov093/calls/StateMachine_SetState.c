#include "nitro/types.h"

typedef struct {
    int state;
    u32 flags;
    int frameCount;
} StateMachine;

void StateMachine_SetState(StateMachine *machine, int state)
{
    machine->state = state;
    machine->frameCount = 0;
}
