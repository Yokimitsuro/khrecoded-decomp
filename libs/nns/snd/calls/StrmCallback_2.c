#include "libs/nns/snd/sndarc_stream_internal.h"

void StrmCallback_2(
    NNSSndStrmCallbackStatus status,
    int numChannels,
    void *buffers[],
    u32 length,
    NNSSndStrmFormat format,
    void *argument)
{
    NNSSndStrmPlayer *player = argument;
    NNSSndStrmCommand *command;
    NNSSndStrmThread *thread;
    int channel;

    if (player->commandCount >= NNS_SND_STRM_BLOCK_NUM - 2) {
        command = NULL;
        while ((command = NNS_FndGetNextListObject(
                    &sPrepareStreamThread.commandList,
                    command)) != NULL) {
            if (command->player == player) {
                break;
            }
        }

        for (channel = 0; channel < command->numChannels; channel++) {
            MI_CpuFill8(
                command->buffers[channel],
                0,
                command->bufferLength);
        }

        NNS_FndRemoveListObject(&sPrepareStreamThread.commandList, command);
        player->commandCount--;
        FreeCommandBuffer(command);
    }

    command = AllocCommandBuffer();
    command->player = player;
    command->status = status;
    command->numChannels = numChannels;
    for (channel = 0; channel < numChannels; channel++) {
        command->buffers[channel] = buffers[channel];
    }
    command->bufferLength = length;

    thread = &sPrepareStreamThread;
    if (status == NNS_SND_STRM_CALLBACK_SETUP &&
        sSoundArcStreamState.prepareThread != NULL) {
        thread = sSoundArcStreamState.prepareThread;
    }

    player->commandCount++;
    NNS_FndAppendListObject(&thread->commandList, command);
    OS_WakeupThread(&thread->threadQueue);
}
