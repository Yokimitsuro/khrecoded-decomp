#include "libs/nns/snd/sndarc_stream_internal.h"

void CloseFileStream(NNSSndStrmPlayer *player)
{
    FS_CloseFile((FSFile *)player->fileStorage);
}
