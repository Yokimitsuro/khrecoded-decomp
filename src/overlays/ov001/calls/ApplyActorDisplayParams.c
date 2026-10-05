#include "nitro/types.h"

typedef struct ActorDisplay {
    u8 pad_000[0x14];
    u8 renderer[0x276];
    u16 unk0 : 5;
    u16 layer : 3;
    u16 unk8 : 8;
    u8 pad_28c[0x5a];
    u16 paramA;
    u8 pad_2e8[2];
    u16 paramB;
} ActorDisplay;

extern void SetNodeRotationXY(void *renderer, int layer, u16 paramA, u16 paramB, int flags);

void ApplyActorDisplayParams(ActorDisplay *display)
{
    SetNodeRotationXY(display->renderer, display->layer, display->paramA, display->paramB, 0);
}
