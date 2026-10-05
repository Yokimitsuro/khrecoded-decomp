#include "src/overlays/ov104/asm_stubs/calls/dsprot_wrappers.h"

extern u32 RC4_Init(void);
extern u32 RC4_InitSBox(void);
extern u32 RC4_EncryptInstructions(void);
extern u32 RC4_DecryptInstructions(void);
extern u32 RC4_InitAndEncryptInstructions(void);
extern u32 RC4_InitAndDecryptInstructions(void);
extern u32 RC4_Byte(void);

asm void __sinit_ov104_020d36b4(void)
{
    orr   r0, pc, #0
    adds  r0, r0, #4
    bne   Encryptor_DecodeFunctionTable
    DCD   RC4_Init + 0x1000
    DCD   DSProt_BSS + 0x1084
    DCD   RC4_InitSBox + 0x1000
    DCD   DSProt_BSS + 0x1030
    DCD   RC4_EncryptInstructions + 0x1000
    DCD   DSProt_BSS + 0x1118
    DCD   RC4_DecryptInstructions + 0x1000
    DCD   DSProt_BSS + 0x1184
    DCD   RC4_InitAndEncryptInstructions + 0x1000
    DCD   DSProt_BSS + 0x1058
    DCD   RC4_InitAndDecryptInstructions + 0x1000
    DCD   DSProt_BSS + 0x1058
    DCD   RC4_Byte + 0x1000
    DCD   DSProt_BSS + 0x1058
    DCD   0
    DCD   0
}
