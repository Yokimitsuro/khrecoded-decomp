#include "src/overlays/ov104/asm_stubs/calls/dsprot_wrappers.h"

extern u32 RunEncrypted_Integrity_MACOwner_IsBad(void);
extern u32 RunEncrypted_Integrity_MACOwner_IsGood(void);
extern u32 RunEncrypted_Integrity_ROMTest_IsBad(void);
extern u32 RunEncrypted_Integrity_ROMTest_IsGood(void);

asm void __sinit_ov104_020d25d0(void)
{
    orr   r0, pc, #0
    adds  r0, r0, #4
    bne   Encryptor_DecodeFunctionTable
    DCD   RunEncrypted_Integrity_MACOwner_IsBad + 0x1000
    DCD   BSS + 0x1024
    DCD   RunEncrypted_Integrity_MACOwner_IsGood + 0x1000
    DCD   BSS + 0x1024
    DCD   RunEncrypted_Integrity_ROMTest_IsBad + 0x1000
    DCD   BSS + 0x1024
    DCD   RunEncrypted_Integrity_ROMTest_IsGood + 0x1000
    DCD   BSS + 0x1024
    DCD   0
    DCD   0
}
