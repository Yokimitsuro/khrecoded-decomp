#include "nitro/types.h"
#include "nitro/fx_types.h"

#define INT_TO_FX32(n) ((fx32)((float)(n) > 0 ? 0.5f + 4096.0f * (float)(n) : 4096.0f * (float)(n) - 0.5f))

typedef struct {
    int state;
    u32 flags;
    int frameCount;
} StateMachine;

extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void func_ov093_020c36bc(StateMachine *machine, fx32 progress);
extern void StateMachine_SetState(StateMachine *machine, int state);
extern void SetBgSubLayerVisible(StateMachine *machine, BOOL visible);

void FadeInPopup(StateMachine *machine)
{
    fx32 progress = FX_Div(INT_TO_FX32(machine->frameCount), 0x2000);

    func_ov093_020c36bc(machine, progress);
    if (progress == 0x1000) {
        StateMachine_SetState(machine, 4);
    }
    SetBgSubLayerVisible(machine, TRUE);
    machine->frameCount++;
}
