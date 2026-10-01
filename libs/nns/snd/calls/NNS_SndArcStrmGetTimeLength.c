typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct NNSSndStrmPlayer {
    unsigned char reserved0[0xcc];
    u16 sampleRate;
    unsigned char reserved1[6];
    u32 loopEnd;
    unsigned char reserved2[0x90];
    u32 curSample;
} NNSSndStrmPlayer;

typedef struct NNSSndStrmHandle {
    NNSSndStrmPlayer *player;
} NNSSndStrmHandle;

extern u64 _ll_udiv(u64 numerator, u64 denominator);

static inline int NNS_SndStrmHandleIsValid(const NNSSndStrmHandle *handle)
{
    return handle->player != 0;
}

u32 NNS_SndArcStrmGetTimeLength(NNSSndStrmHandle *handle)
{
    NNSSndStrmPlayer *player;
    u64 value;

    if (!NNS_SndStrmHandleIsValid(handle)) return 0;
    player = handle->player;
    value = player->loopEnd;
    value *= 1000;
    value = _ll_udiv(value, player->sampleRate);
    return (u32)value;
}