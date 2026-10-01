#ifndef NITRO_OS_EXCEPTION_INTERNAL_H
#define NITRO_OS_EXCEPTION_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

typedef struct OSiExceptionState {
    void *debuggerHandler;
    u32 reserved;
    u32 originalHandler;
} OSiExceptionState;

extern OSiExceptionState OSi_ExceptionState;

u32 OSi_GetOriginalExceptionHandler(void);

#endif
