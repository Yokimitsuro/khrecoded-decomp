#include "libs/nns/snd/sndarc_internal.h"

inline void *GetSoundArchivePointer(void *base, u32 offset)
{
    if (offset == 0) {
        return NULL;
    }
    return (u8 *)base + offset;
}

const char *GetSoundArchiveSymbol(
    const NNSSndArcOffsetTable *table,
    int index,
    const void *base)
{
    u32 offset;

    if (index < 0) {
        return sNullSoundArchiveSymbol;
    }
    if ((u32)index >= table->count) {
        return sNullSoundArchiveSymbol;
    }

    offset = table->offsets[index];
    if (offset == 0) {
        return sNullSoundArchiveSymbol;
    }

    return GetSoundArchivePointer((void *)base, offset);
}
