#include "nitro/types.h"

typedef void (*OSIrqFunction)(void);

extern void OSi_IrqDummy(void);
extern void OSi_IrqDma0(void);
extern void OSi_IrqDma1(void);
extern void OSi_IrqDma2(void);
extern void OSi_IrqDma3(void);
extern void OSi_IrqTimer0(void);
extern void OSi_IrqTimer1(void);
extern void OSi_IrqTimer2(void);
extern void OSi_IrqTimer3(void);

/* The DTCM autoload begins with the NitroSDK IRQ handler table. */
OSIrqFunction SDK_AUTOLOAD_DTCM_START[22] = {
    OSi_IrqDummy,
    OSi_IrqDummy,
    OSi_IrqDummy,
    OSi_IrqTimer0,
    OSi_IrqTimer1,
    OSi_IrqTimer2,
    OSi_IrqTimer3,
    OSi_IrqDummy,
    OSi_IrqDma0,
    OSi_IrqDma1,
    OSi_IrqDma2,
    OSi_IrqDma3,
    OSi_IrqDummy,
    OSi_IrqDummy,
    OSi_IrqDummy,
    OSi_IrqDummy,
    OSi_IrqDummy,
    OSi_IrqDummy,
    OSi_IrqDummy,
    OSi_IrqDummy,
    OSi_IrqDummy,
    OSi_IrqDummy,
};
