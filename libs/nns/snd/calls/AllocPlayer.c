typedef unsigned char u8;
typedef int BOOL;

struct NNSSndStrmPlayer;
typedef struct NNSSndStrmHandle {
    struct NNSSndStrmPlayer *player;
} NNSSndStrmHandle;

typedef struct NNSSndStrmPlayer {
    u8 reserved0[0x118];
    int activeFlag : 1;
    int remainingFlags : 31;
    u8 reserved1[0x18];
    void *buffer;
    u8 reserved2[0x1c];
    NNSSndStrmHandle *handle;
    int priority;
    u8 reserved3[0x20];
} NNSSndStrmPlayer;

extern NNSSndStrmPlayer sStrmPlayers[4];
extern void NNS_SndStrmHandleRelease(NNSSndStrmHandle *handle);
extern void ForceStopStrm_2(NNSSndStrmPlayer *player);

static inline BOOL NNS_SndStrmHandleIsValid(const NNSSndStrmHandle *handle)
{
    return handle->player != 0;
}

NNSSndStrmPlayer *AllocPlayer(NNSSndStrmHandle *handle, int playerNo, int priority)
{
    NNSSndStrmPlayer *player;

    if (NNS_SndStrmHandleIsValid(handle)) {
        NNS_SndStrmHandleRelease(handle);
    }
    player = &sStrmPlayers[playerNo];
    if (player->buffer == 0) return 0;
    if (player->activeFlag) {
        if (priority < player->priority) return 0;
        ForceStopStrm_2(player);
    }
    player->priority = priority;
    player->activeFlag = 1;
    player->handle = handle;
    handle->player = player;
    return player;
}