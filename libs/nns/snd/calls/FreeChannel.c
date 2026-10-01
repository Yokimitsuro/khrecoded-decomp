typedef struct NNSSndStrmPlayer {
    unsigned char stream[0x128];
    int allocChannelCount;
} NNSSndStrmPlayer;

extern void NNS_SndStrmFreeChannel(void *stream);

void FreeChannel(NNSSndStrmPlayer *player)
{
    if (player->allocChannelCount == 0) {
        return;
    }
    player->allocChannelCount--;
    if (player->allocChannelCount == 0) {
        NNS_SndStrmFreeChannel(&player->stream);
    }
}