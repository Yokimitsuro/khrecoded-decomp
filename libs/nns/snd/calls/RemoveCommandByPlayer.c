#include "libs/nns/snd/sndarc_stream_internal.h"

void RemoveCommandByPlayer(
    NNSFndList *commandList,
    const NNSSndStrmPlayer *player)
{
    u32 interruptState;
    NNSSndStrmCommand *command;
    NNSSndStrmCommand *next;

    interruptState = OS_DisableInterrupts();

    for (command = NNS_FndGetNextListObject(commandList, NULL);
         command != NULL;
         command = next) {
        next = NNS_FndGetNextListObject(commandList, command);

        if (command->player == player) {
            NNS_FndRemoveListObject(commandList, command);
            FreeCommandBuffer(command);
        }
    }

    OS_RestoreInterrupts(interruptState);
}
