#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageEventHeader {
    u16 type;
    u8 pad_02[2];
    u16 param;
    u8 pad_06[2];
    s8 layer;
    u8 flagsLow : 6;
    u8 linked : 1;
    u8 flagsHigh : 1;
    u16 objectId;
    u16 actorId;
    u8 pad_0E;
    s8 baseLayer;
    u16 sessionId;
    u8 pad_12[2];
    u32 state;
    u8 pad_18[4];
    VecFx32 position;
} StageEventHeader;

extern void MI_CpuFill8(void *dest, int value, u32 size);
extern int func_ov001_02063a24(void);
extern u16 func_ov001_020644c0(void);

void InitStageEventHeader(StageEventHeader *header, u16 type, u16 objectId, u16 actorId, u16 layer,
                                   const VecFx32 *position, u16 param)
{
    u16 sessionId = 0;

    MI_CpuFill8(header, 0, sizeof(*header));
    header->param = param;
    header->state = 0;
    header->type = type;
    header->objectId = objectId;
    header->actorId = actorId;
    header->layer = layer;
    header->baseLayer = layer;
    header->linked = 0;
    header->position = *position;
    if (func_ov001_02063a24()) {
        sessionId = func_ov001_020644c0();
    }
    header->sessionId = sessionId;
}
