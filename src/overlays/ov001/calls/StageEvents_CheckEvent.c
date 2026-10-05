#include "nitro/types.h"

extern int data_ov001_0209f2e8;
extern BOOL func_ov001_0209c5f0(u16 eventIndex, s16 filterId, int flags);

BOOL StageEvents_CheckEvent(u16 eventIndex)
{
    if (data_ov001_0209f2e8 != -1) {
        return func_ov001_0209c5f0(eventIndex, -1, 0);
    }
    return FALSE;
}
