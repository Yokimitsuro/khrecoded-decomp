typedef unsigned char u8;
typedef int BOOL;

typedef struct NNSSndStrmPlayer {
    unsigned char stream[0x128];
    int allocChannelCount;
} NNSSndStrmPlayer;

extern BOOL NNS_SndStrmAllocChannel(void *stream, int numChannels, const u8 channelList[]);

BOOL AllocChannel(NNSSndStrmPlayer *player, int numChannels, const u8 channelList[])
{
    if (player->allocChannelCount == 0) {
        if (!NNS_SndStrmAllocChannel(&player->stream, numChannels, channelList)) {
            return 0;
        }
    }
    player->allocChannelCount++;
    return 1;
}