#include "src/overlays/ov104/asm_stubs/calls/dsprot_wrappers.h"

extern u32 ROMTest_IsBad(void);

asm u32 RunEncrypted_ROMTest_IsBad(void)
{
    orr    ip, pc, pc
    ands   ip, ip, ip
    moveq  ip, #0
    addne  ip, ip, #0x1c
    ldr    ip, [ip, #0x14]
    sub    ip, ip, #0x1000
    stmfd  sp!, {ip}
    orr    ip, pc, pc
    ldmfd  sp!, {pc}
    DCD    BSS + 1
    DCD    BSS + 0x9145
    DCD    ROMTest_IsBad + 0x1000
    DCD    BSS + 0x123c
    DCD    0
    DCD    Encryptor_DecryptionWrapperFragment + 0x1000
}
