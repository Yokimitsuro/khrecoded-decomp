typedef struct NNSSndStrmHandle NNSSndStrmHandle;

typedef struct NNSSndStrmPlayer {
    unsigned char padding000[0x154];
    NNSSndStrmHandle *handle;
} NNSSndStrmPlayer;

struct NNSSndStrmHandle {
    NNSSndStrmPlayer *player;
};

void NNS_SndStrmHandleRelease(NNSSndStrmHandle *handle)
{
    if (handle->player == 0) {
        return;
    }

    handle->player->handle = 0;
    handle->player = 0;
}