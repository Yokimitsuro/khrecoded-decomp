#include "libs/nns/snd/sndarc_stream_internal.h"

void OnDataEnd(NNSSndStrmPlayer *player)
{
    NNSSndArcStrmCallbackInfo info;
    NNSSndArcStrmCallbackParam parameter;
    const NNSSndArcStrmInfo *streamInfo;
    u8 oldFormat;
    u16 oldSampleRate;
    u64 sample;
    BOOL result;

    info.playerNo = player->playerNo;
    info.streamNo = player->streamNo;

    parameter.streamNo = player->streamNo;
    parameter.offset = 0;

    result = player->archiveCallback(
        NNS_SND_ARC_STRM_CALLBACK_DATA_END,
        &info,
        &parameter,
        player->archiveCallbackArgument);
    if (!result) {
        return;
    }

    streamInfo = NNS_SndArcGetStrmInfo(parameter.streamNo);
    if (streamInfo == NULL) {
        return;
    }

    oldFormat = player->info.format;
    oldSampleRate = player->info.sampleRate;

    player->closeStream(player);
    SetupStreamFunction(player, streamInfo->fileId);

    if (!player->openStream(player, streamInfo->fileId)) {
        return;
    }
    if (oldSampleRate != player->info.sampleRate) {
        return;
    }
    if ((oldFormat == NNS_SND_STRM_DATA_FORMAT_PCM8 &&
         player->info.format != NNS_SND_STRM_DATA_FORMAT_PCM8) ||
        (oldFormat != NNS_SND_STRM_DATA_FORMAT_PCM8 &&
         player->info.format == NNS_SND_STRM_DATA_FORMAT_PCM8)) {
        return;
    }

    player->streamNo = parameter.streamNo;
    sample = player->info.sampleRate;
    sample *= parameter.offset;
    sample /= 1000;
    player->currentSample = (u32)sample;
    if (player->currentSample != 0 &&
        player->info.format == NNS_SND_STRM_DATA_FORMAT_ADPCM) {
        player->dirtyFlag = TRUE;
    } else {
        player->dirtyFlag = FALSE;
    }

    player->finishFlag = FALSE;
}
