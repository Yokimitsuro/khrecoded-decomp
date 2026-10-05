#include "src/overlays/ov104/asm_stubs/calls/dsprot_wrappers.h"

extern u32 DetectFlashcart(void);

asm u32 __DSProt_DetectFlashcart(void)
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
    DCD    DSProt_BSS + 1
    DCD    DSProt_BSS + 0x18a82
    DCD    DetectFlashcart + 0x1000
    DCD    DSProt_BSS + 0x108c
    DCD    0
    DCD    Encryptor_DecryptionWrapperFragment + 0x1000
}
