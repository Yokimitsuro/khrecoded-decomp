#include "src/overlays/ov104/calls/dsprot_encryptor.h"

void *Encryptor_DecryptFunction(u32 key, u32 func_addr, u32 size) {
    u32 expanded_key[4];
    void *func_ptr;

    func_ptr = (void *)func_addr;
    func_ptr -= ENC_VAL_1;

    size -= (u32)&DSProt_BSS + ENC_VAL_1;
    key -= (u32)&DSProt_BSS + ENC_VAL_1;

    expandRC4Key(key, size, expanded_key);
    RC4_InitAndDecryptInstructions(expanded_key, func_ptr, func_ptr, size);
    clearDataAndInstructionCache();

    return func_ptr;
}
