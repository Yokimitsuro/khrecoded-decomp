#include "libs/nns/snd/sndarc_internal.h"

extern BOOL NNS_SndArcSetup(
    NNSSndArc *arc,
    NNSSndHeapHandle heap,
    BOOL symbolLoadFlag);

void NNS_SndArcInit(
    NNSSndArc *arc,
    const char *filePath,
    NNSSndHeapHandle heap,
    BOOL symbolLoadFlag)
{
    BOOL result;

    arc->info = NULL;
    arc->fat = NULL;
    arc->symbol = NULL;
    arc->loadBlockSize = 0;
    arc->reservedAfterFileId[0] = 0;
    arc->reservedAfterFileId[1] = 0;
    arc->reservedAfterFileId[2] = 0;

    if (FS_ConvertPathToFileID(&arc->fileId, filePath)) {
        FS_InitFile(&arc->file);
        result = FS_OpenFileFast(&arc->file, arc->fileId);
        if (!result) {
            return;
        }
    } else {
        arc->fileId.archive = NULL;
        arc->fileId.fileId = (u32)-1;
        result = FS_OpenFileEx(&arc->file, filePath, 1);
        if (!result) {
            return;
        }
    }

    arc->fileOpen = TRUE;
    if (NNS_SndArcSetup(arc, heap, symbolLoadFlag)) {
        sCurrentSoundArchive = arc;
    }
}
