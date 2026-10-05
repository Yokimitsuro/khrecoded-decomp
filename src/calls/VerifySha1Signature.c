#include "nitro/types.h"

extern void ComputeHash(void *digest, const void *data, u32 len);
extern int CompareByteStrings(const void *a, const void *b, u32 len);

typedef struct SignedBlob {
    s32 magic;
    u8 hash[0x14];
    u8 data[0x3760];
} SignedBlob;

BOOL VerifySha1Signature(SignedBlob *blob) {
    u8 digest[0x14];

    if (blob->magic != -0x3c086c5d) {
        return 0;
    }
    ComputeHash(digest, blob->data, 0x3760);
    if (CompareByteStrings(digest, blob->hash, 0x14) == 0) {
        return 1;
    }
    return 0;
}
