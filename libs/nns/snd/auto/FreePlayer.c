typedef unsigned int u32;

typedef struct NNSSndStrmHandle {
    void *player;
} NNSSndStrmHandle;

typedef struct NNSSndStrmPlayer {
    unsigned char reserved0[0x118];
    u32 flags;
    unsigned char reserved1[0x38];
    NNSSndStrmHandle *handle;
} NNSSndStrmPlayer;

void FreePlayer(NNSSndStrmPlayer *player)
{
    if (player->handle != 0) {
        player->handle->player = 0;
        player->handle = 0;
    }
    player->flags &= ~1;
    player->flags &= ~4;
    player->flags &= ~2;
}