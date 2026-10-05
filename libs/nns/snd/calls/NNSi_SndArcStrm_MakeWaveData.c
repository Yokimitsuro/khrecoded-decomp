#include "libs/nns/snd/sndarc_stream_internal.h"

static inline short DecodeAdpcm(int code, NNSSndAdpcmState *state)
{
    int step;
    int sample;
    int index;
    int delta;

    sample = state->previousSample;
    index = state->previousIndex;
    step = cAdpcmStepSizeTable[index];

    delta = step >> 3;
    if (code & 4) {
        delta += step;
    }
    if (code & 2) {
        delta += step >> 1;
    }
    if (code & 1) {
        delta += step >> 2;
    }

    if (code & 8) {
        sample -= delta;
        if (sample < -32768) {
            sample = -32768;
        }
    } else {
        sample += delta;
        if (sample > 32767) {
            sample = 32767;
        }
    }

    index += cAdpcmIndexTable[code];
    if (index < 0) {
        index = 0;
    } else if (index > NNS_SND_ADPCM_INDEX_COUNT - 1) {
        index = NNS_SND_ADPCM_INDEX_COUNT - 1;
    }

    state->previousSample = (short)sample;
    state->previousIndex = (u8)index;
    return (short)sample;
}

void NNSi_SndArcStrm_MakeWaveData(NNSSndStrmCommand *command)
{
    NNSSndStrmPlayer *player = command->player;
    BOOL loopFlag;
    long destinationOffset;
    u32 remainingSize;
    u32 blockNo;
    u32 blockSize;
    u32 blockSamples;
    u32 blockSampleOffset;
    u32 blockOffset;
    u32 streamOffset;
    u32 samples;
    u32 size;
    u32 readSize;
    int channel;

    if (player->finishFlag && player->finishCounter > 0) {
        player->finishCounter--;
    }

    destinationOffset = 0;
    remainingSize = command->bufferLength;

    while (remainingSize > 0) {
        if (player->finishFlag) {
            for (channel = 0; channel < command->numChannels; channel++) {
                MI_CpuFill8(
                    (u8 *)command->buffers[channel] + destinationOffset,
                    0,
                    remainingSize);
            }
            break;
        }

        blockNo = player->currentSample / player->info.blockSamples;
        if (blockNo < player->info.numBlocks - 1) {
            blockSize = player->info.blockSize;
            blockSamples = player->info.blockSamples;
        } else {
            blockSize = player->info.lastBlockSize;
            blockSamples = player->info.lastBlockSamples;
        }

        blockSampleOffset = player->currentSample;
        blockSampleOffset -= blockNo * player->info.blockSamples;

        samples = remainingSize;
        if (player->info.format != NNS_SND_STRM_DATA_FORMAT_PCM8) {
            samples >>= 1;
        }

        if (player->dirtyFlag) {
            if (blockSampleOffset == 0) {
                player->dirtyFlag = FALSE;
            } else {
                samples = blockSampleOffset;
                blockSampleOffset = 0;
            }
        }

        loopFlag = FALSE;
        if (blockSampleOffset + samples >= blockSamples) {
            samples = blockSamples - blockSampleOffset;
            if (blockNo >= player->info.numBlocks - 1) {
                if (player->info.loopFlag) {
                    loopFlag = TRUE;
                } else {
                    player->finishFlag = TRUE;
                }
            }
        }

        blockOffset = blockSampleOffset;
        size = samples;
        switch (player->info.format) {
        case NNS_SND_STRM_DATA_FORMAT_PCM8:
            readSize = size;
            break;
        case NNS_SND_STRM_DATA_FORMAT_PCM16:
            blockOffset <<= 1;
            size <<= 1;
            readSize = size;
            break;
        case NNS_SND_STRM_DATA_FORMAT_ADPCM: {
            u32 endSample = blockSampleOffset + samples;

            blockOffset >>= 1;
            endSample++;
            endSample >>= 1;
            readSize = endSample - blockOffset;
            if (blockSampleOffset == 0) {
                readSize += sizeof(NNSSndAdpcmState);
            } else {
                blockOffset += sizeof(NNSSndAdpcmState);
            }
            size <<= 1;
            break;
        }
        }

        streamOffset = blockOffset;
        streamOffset +=
            blockNo * player->info.blockSize * player->info.numChannels;
        streamOffset += player->info.dataOffset;

        for (channel = 0; channel < command->numChannels; channel++) {
            void *destination;
            void *readDestination;

            destination = readDestination =
                (u8 *)command->buffers[channel] + destinationOffset;

            if (channel < player->info.numChannels) {
                int resultSize;

                if (player->info.format == NNS_SND_STRM_DATA_FORMAT_ADPCM) {
                    OS_LockMutex(sDecodeBufferMutex);
                    readDestination = sSoundArcStreamState.decodeBuffer;
                }

                resultSize = player->readStream(
                    player,
                    readDestination,
                    readSize,
                    streamOffset + channel * blockSize);

                if (resultSize != readSize) {
                    size = 0;
                    samples = 0;
                    loopFlag = FALSE;
                    player->finishFlag = TRUE;
                    if (player->info.format ==
                        NNS_SND_STRM_DATA_FORMAT_ADPCM) {
                        OS_UnlockMutex(sDecodeBufferMutex);
                    }
                    break;
                }

                if (player->info.format == NNS_SND_STRM_DATA_FORMAT_ADPCM) {
                    NNSSndAdpcmState *state = &player->adpcmState[channel];
                    u8 *source = sSoundArcStreamState.decodeBuffer;
                    short *output = destination;
                    u32 sample;
                    u32 endSample;

                    if (blockSampleOffset == 0) {
                        *state = *((NNSSndAdpcmState *)source)++;
                    }

                    endSample = blockSampleOffset + samples;
                    sample = blockSampleOffset;
                    if (sample & 1) {
                        *output++ = DecodeAdpcm((*source >> 4) & 0xf, state);
                        sample++;
                        source++;
                    }
                    while (sample < (endSample & ~1)) {
                        *output++ = DecodeAdpcm(*source & 0xf, state);
                        sample++;
                        *output++ = DecodeAdpcm((*source >> 4) & 0xf, state);
                        sample++;
                        source++;
                    }
                    if (sample < endSample) {
                        *output++ = DecodeAdpcm(*source & 0xf, state);
                        sample++;
                    }
                    OS_UnlockMutex(sDecodeBufferMutex);
                }
            } else if (player->monoFlag) {
                MI_CpuFill8(destination, 0, size);
            } else {
                MI_CpuCopy8(
                    (u8 *)command->buffers[0] + destinationOffset,
                    destination,
                    size);
            }
        }

        if (player->dirtyFlag) {
            player->dirtyFlag = FALSE;
            continue;
        }

        if (loopFlag) {
            player->currentSample = player->info.loopStart;
        } else {
            player->currentSample += samples;
        }

        destinationOffset += size;
        remainingSize -= size;

        if (player->finishFlag && player->archiveCallback != NULL) {
            OnDataEnd(player);
        }
    }

    if (player->streamCallback != NULL) {
        player->streamCallback(
            command->status,
            command->numChannels,
            command->buffers,
            command->bufferLength,
            player->info.format == NNS_SND_STRM_DATA_FORMAT_PCM8
                ? NNS_SND_STRM_FORMAT_PCM8
                : NNS_SND_STRM_FORMAT_PCM16,
            player->streamCallbackArgument);
    }

    for (channel = 0; channel < command->numChannels; channel++) {
        DC_FlushRange(command->buffers[channel], command->bufferLength);
    }

    if (command->status == NNS_SND_STRM_CALLBACK_SETUP) {
        player->prepareFlag = TRUE;
    }
}
