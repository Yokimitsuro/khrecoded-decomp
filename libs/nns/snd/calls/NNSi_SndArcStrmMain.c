typedef unsigned char u8;
typedef unsigned long u32;
typedef short s16;
typedef int BOOL;

typedef struct NNSSndFader {
    int origin;
    int target;
    int counter;
    int frame;
} NNSSndFader;

typedef struct NNSSndStrmPlayer {
    u8 stream[0xf0];
    NNSSndFader fader;
    u8 reserved100[0x18];
    BOOL activeFlag : 1;
    BOOL playFlag : 1;
    BOOL startFlag : 1;
    BOOL fadeOutFlag : 1;
    BOOL dirtyFlag : 1;
    BOOL finishFlag : 1;
    BOOL monoFlag : 1;
    BOOL reservedFlags : 25;
    int finishCounter;
    BOOL prepareFlag;
    u8 reserved124[0x38];
    int initVolume;
    int extVolume;
    int volume;
    u8 reserved168[0x14];
} NNSSndStrmPlayer;

#define NNS_SND_STRM_PLAYER_NUM 4
#define PLAYER_ACTIVE 0x01
#define PLAYER_PLAYING 0x02
#define PLAYER_STARTING 0x04
#define PLAYER_FADE_OUT 0x08

extern const s16 data_02052b1c[128];
extern NNSSndStrmPlayer sStrmPlayers[NNS_SND_STRM_PLAYER_NUM];
extern void NNS_SndStrmStart(void *stream);
extern void NNS_SndStrmSetVolume(void *stream, int volume);
extern int NNSi_SndFaderGet(const NNSSndFader *fader);
extern void NNSi_SndFaderUpdate(NNSSndFader *fader);
extern BOOL NNSi_SndFaderIsFinished(const NNSSndFader *fader);
extern void ForceStopStrm_2(NNSSndStrmPlayer *player);

static inline s16 SND_CalcDecibel(int scale)
{
    return data_02052b1c[scale];
}

void NNSi_SndArcStrmMain(void)
{
    NNSSndStrmPlayer *player;
    int playerNumber;
    int volume;

    for (playerNumber = 0; playerNumber < NNS_SND_STRM_PLAYER_NUM;
         ++playerNumber) {
        player = &sStrmPlayers[playerNumber];

        if (!player->activeFlag) {
            continue;
        }
        if (player->finishCounter == 0) {
            ForceStopStrm_2(player);
            continue;
        }
        if (player->startFlag) {
            if (player->prepareFlag) {
                NNS_SndStrmStart(player->stream);
                player->playFlag = 1;
                player->startFlag = 0;
            }
        }
        if (!player->playFlag) {
            continue;
        }

        NNSi_SndFaderUpdate(&player->fader);
        volume = SND_CalcDecibel(NNSi_SndFaderGet(&player->fader) >> 8) +
                 SND_CalcDecibel(player->initVolume) +
                 SND_CalcDecibel(player->extVolume);
        if (volume != player->volume) {
            NNS_SndStrmSetVolume(player->stream, volume);
            player->volume = volume;
        }

        if (player->fadeOutFlag) {
            if (NNSi_SndFaderIsFinished(&player->fader)) {
                ForceStopStrm_2(player);
            }
        }
    }
}