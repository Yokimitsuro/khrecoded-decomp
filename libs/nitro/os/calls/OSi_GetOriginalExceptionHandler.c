#include "libs/nitro/os/os_exception_internal.h"

u32 OSi_GetOriginalExceptionHandler(void)
{
    return OSi_ExceptionState.originalHandler;
}
