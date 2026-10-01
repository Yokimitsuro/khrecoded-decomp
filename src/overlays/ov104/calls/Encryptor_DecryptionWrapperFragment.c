#include "src/overlays/ov104/calls/dsprot_encryptor.h"

asm u32 Encryptor_DecryptionWrapperFragment(void) {
    stmfd  sp!, {r0-r3}
    str    r10, [ip, #0x10]
    mov    r10, ip
    str    lr, [r10]
    ldmib  r10, {r0-r2}
    bl     Encryptor_DecryptFunction
    mov    ip, r0
    ldmia  sp!, {r0-r3}
    blx    ip
    stmdb  sp!, {r4}
    mov    r4, r0
    ldmib  r10, {r0-r2}
    bl     Encryptor_EncryptFunction
    str    r0, [r10, #4]
    mov    r0, r4
    ldmia  sp!, {r4}
    ldr    lr, [r10]
    str    sp, [r10]
    ldr    r10, [r10, #0x10]
    bx     lr
}
