#include "libs/nns/snd/sndarc_stream_internal.h"

void SetupStreamFunction(NNSSndStrmPlayer *player, u32 fileId)
{
    if (NNS_SndArcGetFileAddress(fileId) == NULL) {
        player->openStream = OpenFileStream;
        player->closeStream = CloseFileStream;
        player->readStream = ReadFileStream;
        player->cancelStream = CancelFileStream;
    } else {
        player->openStream = OpenMemoryStream;
        player->closeStream = CloseMemoryStream;
        player->readStream = ReadMemoryStream;
        player->cancelStream = CancelMemoryStream;
    }
}
