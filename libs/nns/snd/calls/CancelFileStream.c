#include "libs/nns/snd/sndarc_stream_internal.h"

void CancelFileStream(NNSSndStrmPlayer *player)
{
    FS_CancelFile((FSFile *)player->fileStorage);
}
