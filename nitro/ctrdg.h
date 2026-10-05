#ifndef NITRO_CTRDG_H
#define NITRO_CTRDG_H

#include "nitro/types.h"
#include "nitro/os.h"
#include "nitro/hw.h"
#include "nitro/mi.h"

typedef struct CTRDGRomCycle {
    MICartridgeRomCycle1st c1;
    MICartridgeRomCycle2nd c2;
} CTRDGRomCycle;

typedef struct CTRDGLockByProc {
    BOOL locked;
    OSIntrMode irq;
} CTRDGLockByProc;

#endif
