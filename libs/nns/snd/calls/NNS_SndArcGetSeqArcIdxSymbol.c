#include "libs/nns/snd/sndarc_internal.h"

static inline const void *GetSoundArchivePointer(
    const void *base,
    u32 offset)
{
    if (offset == 0) {
        return NULL;
    }
    return (const u8 *)base + offset;
}

const char *NNS_SndArcGetSeqArcIdxSymbol(int seqArcNo, int index)
{
    NNSSndArc *arc = sCurrentSoundArchive;
    const NNSSndArcSeqArcSymbolTable *table;
    const NNSSndArcOffsetTable *symbolTable;

    if (arc->symbol == NULL) {
        return sNullSoundArchiveSymbol;
    }

    table = GetSoundArchivePointer(
        arc->symbol,
        arc->symbol->seqArcOffset);
    if (table == NULL) {
        return sNullSoundArchiveSymbol;
    }
    if (seqArcNo < 0) {
        return sNullSoundArchiveSymbol;
    }
    if ((u32)seqArcNo >= table->count) {
        return sNullSoundArchiveSymbol;
    }

    symbolTable = GetSoundArchivePointer(
        arc->symbol,
        table->entries[seqArcNo].tableOffset);
    if (symbolTable == NULL) {
        return sNullSoundArchiveSymbol;
    }

    return GetSoundArchiveSymbol(symbolTable, index, arc->symbol);
}
