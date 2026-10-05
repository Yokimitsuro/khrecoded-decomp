#include "nitro/types.h"

extern BOOL func_ov047_020c6e30(u16 angle);

BOOL ResolveBlockedAngle(s32 distance, int angle, int referenceAngle, int *outAngle)
{
    int result = angle;

    if (func_ov047_020c6e30(angle)) {
        result = (u16)(angle - referenceAngle < 0 ? angle + 0x4000 : angle - 0x4000);
        if (func_ov047_020c6e30(result)) {
            if (distance >= 0x1800) {
                return FALSE;
            }
            result = angle;
        }
    }
    *outAngle = result;
    return TRUE;
}
