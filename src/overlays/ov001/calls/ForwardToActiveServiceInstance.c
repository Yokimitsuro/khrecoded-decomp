#include "nitro/types.h"

typedef unsigned int UNDEF4;

extern s32 func_ov001_02097aac(s32 service, UNDEF4 arg1, UNDEF4 arg2);
extern s32 func_ov001_0209c114(void);

s32 ForwardToActiveServiceInstance(UNDEF4 unusedArg, UNDEF4 arg1, UNDEF4 arg2)
{
    s32 service;
    s32 result;

    service = func_ov001_0209c114();
    if (service != 0) {
        result = func_ov001_02097aac(service, arg1, arg2);
        return result;
    }
    return 0;
}
