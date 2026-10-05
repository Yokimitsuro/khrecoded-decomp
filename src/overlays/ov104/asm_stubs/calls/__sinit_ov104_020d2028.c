#include "src/overlays/ov104/asm_stubs/calls/dsprot_wrappers.h"

extern u32 __DSProt_DetectFlashcart(void);
extern u32 __DSProt_DetectNotFlashcart(void);
extern u32 __DSProt_DetectEmulator(void);
extern u32 __DSProt_DetectNotEmulator(void);
extern u32 __DSProt_DetectDummy(void);
extern u32 __DSProt_DetectNotDummy(void);

asm void __sinit_ov104_020d2028(void)
{
    orr   r0, pc, #0
    adds  r0, r0, #4
    bne   Encryptor_DecodeFunctionTable
    DCD   __DSProt_DetectFlashcart + 0x1000
    DCD   DSProt_BSS + 0x1024
    DCD   __DSProt_DetectNotFlashcart + 0x1000
    DCD   DSProt_BSS + 0x1024
    DCD   __DSProt_DetectEmulator + 0x1000
    DCD   DSProt_BSS + 0x1024
    DCD   __DSProt_DetectNotEmulator + 0x1000
    DCD   DSProt_BSS + 0x1024
    DCD   __DSProt_DetectDummy + 0x1000
    DCD   DSProt_BSS + 0x1024
    DCD   __DSProt_DetectNotDummy + 0x1000
    DCD   DSProt_BSS + 0x1024
    DCD   0
    DCD   0
    DCD   Garbage + 0x1000
}
