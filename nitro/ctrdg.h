#ifndef NITRO_CTRDG_H
#define NITRO_CTRDG_H

#include "nitro/types.h"
#include "nitro/os.h"
#include "nitro/hw.h"
#include "nitro/mi.h"

#define CTRDG_PXI_COMMAND_TERMINATE 0x0002

typedef struct CTRDGRomCycle {
    MICartridgeRomCycle1st c1;
    MICartridgeRomCycle2nd c2;
} CTRDGRomCycle;

typedef struct CTRDGLockByProc {
    BOOL locked;
    OSIntrMode irq;
} CTRDGLockByProc;

typedef struct CTRDGWork {
    vu16 subpInitialized;
    u16 lockID;
} CTRDGWork;

#endif
