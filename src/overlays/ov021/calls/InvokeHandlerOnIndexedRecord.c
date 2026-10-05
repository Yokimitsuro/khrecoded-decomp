#include "nitro/types.h"

extern s32 *func_ov021_020a8830(void);
extern void SelectModelTrackBlends(s32 addr, u32 value);

void InvokeHandlerOnIndexedRecord(u32 unused0, s32 index, u32 value)
{
    s32 *table = func_ov021_020a8830();
    if (table != 0) {
        SelectModelTrackBlends(*table + index * 0x138, value);
    }
}
