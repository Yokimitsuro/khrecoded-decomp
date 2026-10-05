#include "nitro/types.h"

typedef struct {
    s8 mode;
    s8 kind;
    s16 x;
    s16 y;
} StartParams;

typedef struct {
    s16 kind;
    s16 x;
    s16 y;
    u16 flags;
    u8 pad_08[0x10];
    u32 timer;
    u8 pad_1c[0x20];
    s8 mode;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern void ClearFieldCounters(void);

void ApplyStartParams(StartParams *params)
{
    data_ov031_020bc820->x = params->x;
    data_ov031_020bc820->y = params->y;
    data_ov031_020bc820->kind = params->kind;
    data_ov031_020bc820->flags = 3;
    data_ov031_020bc820->flags |= 0x20;
    data_ov031_020bc820->mode = params->mode;
    data_ov031_020bc820->timer = 0;
    ClearFieldCounters();
}
