typedef unsigned int u32;
typedef int OSIntrMode;

typedef struct NNSFndList NNSFndList;

typedef struct NNSSndStrmPlayer {
    unsigned char reserved[0x124];
    int commandCount;
} NNSSndStrmPlayer;

typedef struct LoadCommand {
    void *previous;
    void *next;
    NNSSndStrmPlayer *player;
    int status;
    int numChannels;
    void *buffer[6];
    u32 bufferLength;
} LoadCommand;

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void NNS_FndRemoveListObject(NNSFndList *list, void *object);
extern void *NNS_FndGetNextListObject(NNSFndList *list, void *object);

LoadCommand *ReadCommandBuffer(NNSFndList *commandList)
{
    OSIntrMode oldInterruptMode;
    LoadCommand *command;

    oldInterruptMode = OS_DisableInterrupts();
    command = (LoadCommand *)NNS_FndGetNextListObject(commandList, 0);
    if (command != 0) {
        NNS_FndRemoveListObject(commandList, command);
        command->player->commandCount--;
    }
    (void)OS_RestoreInterrupts(oldInterruptMode);
    return command;
}