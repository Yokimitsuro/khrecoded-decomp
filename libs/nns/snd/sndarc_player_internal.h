#ifndef NNS_SNDARC_PLAYER_INTERNAL_H
#define NNS_SNDARC_PLAYER_INTERNAL_H

#include "libs/nns/snd/sndarc_loader_internal.h"

enum {
    NNS_SND_PLAYER_NUM = 32,
    NNS_SND_SEQ_ARC_INVALID_OFFSET = 0xffffffff
};

typedef struct NNSSndSeqPlayer NNSSndSeqPlayer;

typedef struct NNSSndHandle {
    NNSSndSeqPlayer *player;
} NNSSndHandle;

typedef struct NNSSndArcPlayerInfo {
    u8 seqMax;
    u8 padding;
    u16 allocChBitFlag;
    u32 heapSize;
} NNSSndArcPlayerInfo;

extern const NNSSndArcPlayerInfo *NNS_SndArcGetPlayerInfo(int playerNo);
extern void NNS_SndPlayerSetPlayableSeqCount(int playerNo, int seqCount);
extern void NNS_SndPlayerSetAllocatableChannel(int playerNo, u32 channelMask);
extern BOOL NNS_SndPlayerCreateHeap(
    int playerNo,
    NNSSndHeapHandle heap,
    u32 size);
extern NNSSndSeqPlayer *NNSi_SndPlayerAllocSeqPlayer(
    NNSSndHandle *handle,
    int playerNo,
    int priority);
extern void NNSi_SndPlayerFreeSeqPlayer(NNSSndSeqPlayer *player);
extern NNSSndHeapHandle NNSi_SndPlayerAllocHeap(
    int playerNo,
    NNSSndSeqPlayer *player);
extern void NNSi_SndPlayerStartSeq(
    NNSSndSeqPlayer *player,
    const void *sequenceBase,
    u32 sequenceOffset,
    const SNDBankData *bank);
extern void NNS_SndPlayerSetInitialVolume(NNSSndHandle *handle, int volume);
extern void NNS_SndPlayerSetChannelPriority(
    NNSSndHandle *handle,
    int priority);
extern void NNS_SndPlayerSetSeqNo(NNSSndHandle *handle, int seqNo);
extern void NNS_SndPlayerSetSeqArcNo(
    NNSSndHandle *handle,
    int seqArcNo,
    int index);
extern const NNSSndSeqArcSeqInfo *NNSi_SndSeqArcGetSeqInfo(
    const NNSSndSeqArc *seqArc,
    int index);
extern BOOL StartSeq(
    NNSSndHandle *handle,
    int playerNo,
    int bankNo,
    int playerPriority,
    const NNSSndArcSeqInfo *info,
    int seqNo);
extern BOOL StartSeqArc(
    NNSSndHandle *handle,
    int playerNo,
    int bankNo,
    int playerPriority,
    const NNSSndSeqArcSeqInfo *sequence,
    const NNSSndSeqArc *seqArc,
    int seqArcNo,
    int index);

#endif
