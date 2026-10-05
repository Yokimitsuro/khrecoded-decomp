#ifndef NITRO_MI_H
#define NITRO_MI_H

#include "nitro/types.h"
#include "nitro/hw.h"

typedef enum MICartridgeRomCycle1st {
    MI_CTRDG_ROMCYCLE1_10 = 0,
    MI_CTRDG_ROMCYCLE1_8,
    MI_CTRDG_ROMCYCLE1_6,
    MI_CTRDG_ROMCYCLE1_18
} MICartridgeRomCycle1st;

typedef enum MICartridgeRomCycle2nd {
    MI_CTRDG_ROMCYCLE2_6 = 0,
    MI_CTRDG_ROMCYCLE2_4
} MICartridgeRomCycle2nd;

typedef enum MIProcessor {
    MI_PROCESSOR_ARM9 = 0,
    MI_PROCESSOR_ARM7
} MIProcessor;

#endif
