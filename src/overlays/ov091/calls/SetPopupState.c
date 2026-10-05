#include "nitro/types.h"

typedef struct {
    s32 state;
    u32 flags;
    s32 stateTimer;
} PopupStateMachine;

void SetPopupState(PopupStateMachine *machine, s32 state)
{
    machine->state = state;
    machine->stateTimer = 0;
}
