#include "libs/nns/snd/sndarc_stream_internal.h"

BOOL PrepareStrm(
    NNSSndStrmHandle *handle,
    const NNSSndArcStrmInfo *streamInfo,
    int playerNo,
    int playerPriority,
    int streamNo,
    u32 offset,
    NNSSndStrmCallback streamCallback,
    void *streamCallbackArgument,
    NNSSndArcStrmCallback archiveCallback,
    void *archiveCallbackArgument)
{
    NNSSndStrmPlayer *player;
    NNSSndStrmFormat format;
    int numChannels;
    u64 sample;
    BOOL result;

    player = AllocPlayer(handle, playerNo, playerPriority);
    if (player == NULL) {
        return FALSE;
    }

    SetupStreamFunction(player, streamInfo->fileId);

    if (!player->openStream(player, streamInfo->fileId)) {
        FreePlayer(player);
        return FALSE;
    }

    sample = player->info.sampleRate;
    sample *= offset;
    sample /= 1000;
    player->currentSample = (u32)sample;

    if (player->currentSample != 0 &&
        player->info.format == NNS_SND_STRM_DATA_FORMAT_ADPCM) {
        player->dirtyFlag = TRUE;
    } else {
        player->dirtyFlag = FALSE;
    }

    player->finishCounter = NNS_SND_STRM_BLOCK_NUM;
    player->finishFlag = FALSE;
    player->playFlag = FALSE;
    player->prepareFlag = FALSE;
    player->startFlag = FALSE;
    player->fadeOutFlag = FALSE;
    player->commandCount = 0;

    player->streamCallback = streamCallback;
    player->streamCallbackArgument = streamCallbackArgument;
    player->archiveCallback = archiveCallback;
    player->archiveCallbackArgument = archiveCallbackArgument;
    player->streamNo = streamNo;

    player->volume = 0;
    player->initialVolume = streamInfo->volume;
    player->externalVolume = 127;

    NNSi_SndFaderInit(&player->fader);
    NNSi_SndFaderSet(&player->fader, 127 << 8, 1);

    switch (player->info.format) {
    case NNS_SND_STRM_DATA_FORMAT_PCM8:
        format = NNS_SND_STRM_FORMAT_PCM8;
        break;
    case NNS_SND_STRM_DATA_FORMAT_PCM16:
    case NNS_SND_STRM_DATA_FORMAT_ADPCM:
        format = NNS_SND_STRM_FORMAT_PCM16;
        break;
    }

    numChannels = player->info.numChannels;
    if (streamInfo->flags & NNS_SND_ARC_STRM_FORCE_STEREO) {
        numChannels = 2;
    }
    if (numChannels > player->numChannels) {
        numChannels = player->numChannels;
    }
    player->monoFlag = numChannels == 1 ? TRUE : FALSE;

    result = AllocChannel(player, numChannels, player->channelNumbers);
    if (!result) {
        player->closeStream(player);
        FreePlayer(player);
        return FALSE;
    }

    result = NNS_SndStrmSetup(
        &player->stream,
        format,
        player->buffer,
        player->bufferSize * numChannels / player->numChannels,
        player->info.timer,
        NNS_SND_STRM_BLOCK_NUM,
        StrmCallback_2,
        player);
    if (!result) {
        FreeChannel(player);
        player->closeStream(player);
        FreePlayer(player);
        return FALSE;
    }

    if (numChannels == 2) {
        NNS_SndStrmSetChannelPan(&player->stream, 0, 0);
        NNS_SndStrmSetChannelPan(&player->stream, 1, 127);
    }

    return TRUE;
}
