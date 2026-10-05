#include "libs/nns/snd/sndarc_stream_internal.h"

BOOL OpenFileStream(NNSSndStrmPlayer *player, u32 fileId)
{
    const char *filePath;
    void *seekCacheBuffer;
    u32 seekCacheSize;
    BOOL opened;
    BOOL cacheSet;

    if (NNS_SndArcReadFile(
            fileId,
            &player->info,
            sizeof(player->info),
            0) != sizeof(player->info)) {
        return FALSE;
    }

    if (!FS_OpenFileFast(
            (FSFile *)player->fileStorage,
            NNS_SndArcGetFileID())) {
        filePath = NNSi_SndArcGetFilePath();
        if (filePath == NULL) {
            return FALSE;
        }

        seekCacheBuffer = NNSi_SndArcGetSeekCacheBuffer();
        seekCacheSize = NNSi_SndArcGetSeekCacheSize();
        if (seekCacheBuffer == NULL) {
            return FALSE;
        }
        if (seekCacheSize == 0) {
            return FALSE;
        }

        opened = FS_OpenFileEx(
            (FSFile *)player->fileStorage,
            filePath,
            1);
        cacheSet = FS_SetSeekCache(
            (FSFile *)player->fileStorage,
            seekCacheBuffer,
            seekCacheSize);
        if (!opened) {
            return FALSE;
        }
        if (!cacheSet) {
            return FALSE;
        }
    }

    player->fileOffset = NNS_SndArcGetFileOffset(fileId);
    return TRUE;
}
