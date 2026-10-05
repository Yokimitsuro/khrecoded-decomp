#include "nitro/types.h"

typedef struct {
    u8 pad[0xa];
    u16 value;
} ParamBlock;

extern ParamBlock *GetSelectionPackedValueBlock(void);
extern void SetParamHalf18(u16 value);

void TrackMaxParamValue(u8 *work)
{
    ParamBlock *params = GetSelectionPackedValueBlock();
    u16 value = params->value;
    if (value > *(u16 *)(work + 0x14d0c)) {
        *(u16 *)(work + 0x14d0c) = value;
    }
    SetParamHalf18(*(u16 *)(work + 0x14d0c));
}
