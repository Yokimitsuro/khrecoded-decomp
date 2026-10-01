#include "libs/nitro/fs/fs_overlay_internal.h"

#define FS_OVERLAY_DIGEST_SIZE 20

extern void MI_CpuFill8(void *destination, int value, u32 size);
extern void MI_CpuCopy8(const void *source, void *destination, u32 size);
extern int MATHi_SetOverlayTableMode(int enabled);
extern void MATH_CalcHMACSHA1(u8 *digest, const void *source, u32 length,
                              const void *key, u32 keyLength);

BOOL FSi_CompareDigest(const u8 *expectedDigest, void *source, int length,
                       BOOL tableMode)
{
    int position;
    u8 digest[FS_OVERLAY_DIGEST_SIZE];
    u8 digestKey[64];
    int previousMode = 0;

    MI_CpuFill8(digest, 0, sizeof(digest));
    MI_CpuCopy8(FSiOverlayContext.digestKey, digestKey,
                FSiOverlayContext.digestKeyLength);

    if (tableMode) {
        previousMode = MATHi_SetOverlayTableMode(1);
    }
    MATH_CalcHMACSHA1(digest, source, length, digestKey,
                      FSiOverlayContext.digestKeyLength);
    if (tableMode) {
        (void)MATHi_SetOverlayTableMode(previousMode);
    }

    for (position = 0; position < sizeof(digest); position += sizeof(u32)) {
        if (*(const u32 *)(digest + position) !=
            *(const u32 *)(expectedDigest + position)) {
            break;
        }
    }
    return position == sizeof(digest);
}
