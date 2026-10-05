#include "src/overlays/ov104/asm_stubs/calls/dsprot_wrappers.h"

extern u32 RunEncrypted_ROMTest_IsBad(void);
extern u32 RunEncrypted_ROMTest_IsGood(void);
extern u32 RunEncrypted_MACOwner_IsBad(void);
extern u32 RunEncrypted_MACOwner_IsGood(void);
extern u32 RunEncrypted_ROMUtil_CRC32(void);
extern u32 RunEncrypted_Dummy_IsBad(void);
extern u32 RunEncrypted_Dummy_IsGood(void);

asm void __sinit_ov104_020d31fc(void)
{
    orr   r0, pc, #0
    adds  r0, r0, #4
    bne   Encryptor_DecodeFunctionTable
    DCD   RunEncrypted_ROMTest_IsBad + 0x1000
    DCD   DSProt_BSS + 0x1024
    DCD   RunEncrypted_ROMTest_IsGood + 0x1000
    DCD   DSProt_BSS + 0x1024
    DCD   RunEncrypted_MACOwner_IsBad + 0x1000
    DCD   DSProt_BSS + 0x1024
    DCD   RunEncrypted_MACOwner_IsGood + 0x1000
    DCD   DSProt_BSS + 0x1024
    DCD   RunEncrypted_ROMUtil_CRC32 + 0x1000
    DCD   DSProt_BSS + 0x1024
    DCD   RunEncrypted_Dummy_IsBad + 0x1000
    DCD   DSProt_BSS + 0x1024
    DCD   RunEncrypted_Dummy_IsGood + 0x1000
    DCD   DSProt_BSS + 0x1024
    DCD   0
    DCD   0
}
