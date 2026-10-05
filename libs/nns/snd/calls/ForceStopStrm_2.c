typedef unsigned char u8;

typedef struct NNSSndStrmThread {
    u8 reserved[0x10c8];
    u8 mutex[1];
} NNSSndStrmThread;

typedef struct SoundArcStreamState {
    void *reserved;
    NNSSndStrmThread *prepareThread;
} SoundArcStreamState;

typedef struct NNSSndStrmPlayer {
    u8 stream[0x118];
    int activeFlag : 1;
    int playFlag : 1;
    int remainingFlags : 30;
    u8 reserved[0x5c];
    void (*cancelStreamFunc)(struct NNSSndStrmPlayer *player);
} NNSSndStrmPlayer;

extern u8 sSoundArcStreamMutex;
extern SoundArcStreamState sSoundArcStreamState;
extern void OS_LockMutex(void *mutex);
extern void OS_UnlockMutex(void *mutex);
extern void NNS_SndStrmStop(void *stream);
extern void ShutdownStreamPlayer(NNSSndStrmPlayer *player);

void ForceStopStrm_2(NNSSndStrmPlayer *player)
{
    OS_LockMutex(&sSoundArcStreamMutex);
    if (sSoundArcStreamState.prepareThread) {
        OS_LockMutex(&sSoundArcStreamState.prepareThread->mutex);
    }
    if (player->playFlag) {
        NNS_SndStrmStop(&player->stream);
    }
    if (player->activeFlag) {
        player->cancelStreamFunc(player);
    }
    ShutdownStreamPlayer(player);
    OS_UnlockMutex(&sSoundArcStreamMutex);
    if (sSoundArcStreamState.prepareThread) {
        OS_UnlockMutex(&sSoundArcStreamState.prepareThread->mutex);
    }
}
