#ifndef NNS_SND_INTERNAL_H
#define NNS_SND_INTERNAL_H

#include "nitro/types.h"
#include "nnsys/snd.h"

#define NNS_SND_PLAYER_COUNT 16
#define NNS_SND_LOGICAL_PLAYER_COUNT 32
#define SND_ALARM_COUNT 8

typedef struct NNSSndGlobalState {
    s8 activeState;
    u8 padding1[3];
    s32 unk4;
    u32 padding2;
    BOOL initialized;
    void (*preSleepCallback)(void *arg);
    void *preSleepArg;
    u8 preSleepLink[8];
    void *(*postSleepCallback)(void);
    void *postSleepArg;
} NNSSndGlobalState;

typedef struct NNSSndResourceLocks {
    u32 capture;
    u32 alarm;
    u32 channel;
} NNSSndResourceLocks;

extern NNSSndGlobalState sSndGlobalState;
extern NNSSndResourceLocks sSndResourceLocks;
extern NNSFndList sSndSeqPlayerList;
extern NNSSndSeqPlayer sSndSeqPlayers[NNS_SND_PLAYER_COUNT];
extern NNSSndPlayer sSndPlayers[NNS_SND_LOGICAL_PLAYER_COUNT];

#endif
