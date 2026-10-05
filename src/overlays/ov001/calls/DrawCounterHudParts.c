#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CounterHud {
    u8 pad_000[0x10];
    u8 leftPart[0xc];
    u8 rightPart[0xc];
    u8 pad_028[0xc0];
    fx32 partX;
    u8 pad_0EC[0xa8];
    void *currentPart;
} CounterHud;

extern void UpdateTimerHud(CounterHud *hud);
extern void UpdateAnimatedCounterHud(CounterHud *hud);

void DrawCounterHudParts(CounterHud *hud)
{
    hud->currentPart = hud->leftPart;
    hud->partX = 0xbd000;
    UpdateTimerHud(hud);
    hud->currentPart = hud->rightPart;
    hud->partX = 0x23000;
    UpdateAnimatedCounterHud(hud);
}
