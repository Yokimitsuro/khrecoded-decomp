#include "libs/nns/snd/sndarc_internal.h"

extern void InfoDisposeCallback(
    void *memory,
    u32 size,
    u32 data1,
    u32 data2);
extern void FatDisposeCallback(
    void *memory,
    u32 size,
    u32 data1,
    u32 data2);
extern void SymbolDisposeCallback(
    void *memory,
    u32 size,
    u32 data1,
    u32 data2);

BOOL NNS_SndArcSetup(
    NNSSndArc *arc,
    NNSSndHeapHandle heap,
    BOOL symbolLoadFlag)
{
    BOOL result;
    int readSize;

    result = FS_SeekFile(&arc->file, 0, FS_SEEK_SET);
    if (!result) {
        return FALSE;
    }

    readSize = FS_ReadFile(&arc->file, &arc->header, sizeof(arc->header));
    if (readSize != sizeof(arc->header)) {
        return FALSE;
    }

    if (heap != NNS_SND_HEAP_INVALID_HANDLE) {
        arc->info = NNS_SndHeapAlloc(
            heap,
            arc->header.infoSize,
            InfoDisposeCallback,
            (u32)arc,
            0);
        if (arc->info == NULL) {
            return FALSE;
        }
        result = FS_SeekFile(
            &arc->file,
            (int)arc->header.infoOffset,
            FS_SEEK_SET);
        if (!result) {
            return FALSE;
        }
        readSize = FS_ReadFile(
            &arc->file,
            arc->info,
            (int)arc->header.infoSize);
        if (readSize != arc->header.infoSize) {
            return FALSE;
        }

        arc->fat = NNS_SndHeapAlloc(
            heap,
            arc->header.fatSize,
            FatDisposeCallback,
            (u32)arc,
            0);
        if (arc->fat == NULL) {
            return FALSE;
        }
        result = FS_SeekFile(
            &arc->file,
            (int)arc->header.fatOffset,
            FS_SEEK_SET);
        if (!result) {
            return FALSE;
        }
        readSize = FS_ReadFile(
            &arc->file,
            arc->fat,
            (int)arc->header.fatSize);
        if (readSize != arc->header.fatSize) {
            return FALSE;
        }

        if (symbolLoadFlag && arc->header.symbolDataSize > 0) {
            arc->symbol = NNS_SndHeapAlloc(
                heap,
                arc->header.symbolDataSize,
                SymbolDisposeCallback,
                (u32)arc,
                0);
            if (arc->symbol == NULL) {
                return FALSE;
            }
            result = FS_SeekFile(
                &arc->file,
                (int)arc->header.symbolDataOffset,
                FS_SEEK_SET);
            if (!result) {
                return FALSE;
            }
            readSize = FS_ReadFile(
                &arc->file,
                arc->symbol,
                (int)arc->header.symbolDataSize);
            if (readSize != arc->header.symbolDataSize) {
                return FALSE;
            }
        }
    }

    return TRUE;
}
