#ifndef NITRO_OS_H
#define NITRO_OS_H

#include "nitro/types.h"

typedef int OSIntrMode;
typedef u32 OSIrqMask;
typedef void *OSMessage;
typedef struct OSMessageQueue OSMessageQueue;

#define OS_IME_ENABLE 1
#define OS_MESSAGE_NOBLOCK 0
#define OS_MESSAGE_BLOCK 1

#endif
