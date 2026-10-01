#include "src/overlays/ov104/asm_stubs/calls/dsprot_wrappers.h"

extern u32 ROMUtil_CRC32(void);

asm u32 RunEncrypted_ROMUtil_CRC32(void)
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
    DCD    BSS + 0x9025
    DCD    ROMUtil_CRC32 + 0x1000
    DCD    BSS + 0x1090
    DCD    0
    DCD    Encryptor_DecryptionWrapperFragment + 0x1000
}
