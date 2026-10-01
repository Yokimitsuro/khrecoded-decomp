#include "src/overlays/ov104/calls/dsprot_integrity.h"

u32 Integrity_ROMTest_IsBad(void) {
    u8 *addr;

    addr = (u8 *)ADDR_PLUS_ADDEND(RunEncrypted_ROMTest_IsBad, ENC_VAL_1) - (ENC_VAL_1 * 2);

    return checkDecryptionWrapper(addr, PRIME_INTEGRITY * PRIME_FALSE, PRIME_INTEGRITY * PRIME_TRUE);
}
