#include "src/overlays/ov104/asm_stubs/calls/dsprot_wrappers.h"

extern u32 Encryptor_EncryptFunction(void);
extern u32 Encryptor_DecryptFunction(void);
extern u32 Encryptor_DecryptionWrapperFragment(void);

asm void __sinit_ov104_020d2958(void)
{
    orr   r0, pc, #0
    adds  r0, r0, #4
    bne   Encryptor_DecodeFunctionTable
    DCD   Encryptor_EncryptFunction + 0x1000
    DCD   DSProt_BSS + 0x10d0
    DCD   Encryptor_DecryptFunction + 0x1000
    DCD   DSProt_BSS + 0x10bc
    DCD   Encryptor_DecryptionWrapperFragment + 0x1000
    DCD   DSProt_BSS + 0x1050
    DCD   0
    DCD   0
}
