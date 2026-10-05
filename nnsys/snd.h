#ifndef NNSYS_SND_H
#define NNSYS_SND_H

#include "nitro/types.h"

typedef struct NNSFndLink {
    void *prevObject;
    void *nextObject;
} NNSFndLink;

typedef struct NNSFndList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef struct NNSSndHeap *NNSSndHeapHandle;
typedef void (*NNSSndHeapDisposeCallback)(void *mem, u32 size, u32 data1, u32 data2);

typedef struct NNSSndFader {
    int origin;
    int target;
    int counter;
    int frame;
} NNSSndFader;

struct NNSSndSeqPlayer;
struct NNSSndPlayer;
struct NNSSndPlayerHeap;
typedef struct SNDBankData SNDBankData;

typedef struct NNSSndHandle {
    struct NNSSndSeqPlayer *player;
} NNSSndHandle;

enum NNSSndSeqPlayerStatus {
    NNS_SND_SEQ_PLAYER_STATUS_STOP,
    NNS_SND_SEQ_PLAYER_STATUS_PLAY,
    NNS_SND_SEQ_PLAYER_STATUS_FADEOUT
};

typedef enum NNSSndPlayerSeqType {
    NNS_SND_PLAYER_SEQ_TYPE_INVALID,
    NNS_SND_PLAYER_SEQ_TYPE_SEQ,
    NNS_SND_PLAYER_SEQ_TYPE_SEQARC
} NNSSndPlayerSeqType;

typedef struct NNSSndSeqPlayer {
    NNSSndHandle *handle;
    struct NNSSndPlayer *player;
    struct NNSSndPlayerHeap *heap;
    NNSFndLink playerLink;
    NNSFndLink prioLink;
    NNSSndFader fader;
    u8 status;
    u8 startFlag;
    u8 pauseFlag;
    u8 prepareFlag;
    u32 commandTag;
    u16 seqType;
    u16 padding;
    u16 seqNo;
    u16 seqArcIndex;
    u8 playerNo;
    u8 priority;
    s16 volume;
    u8 initialVolume;
    u8 externalVolume;
    u16 padding2;
} NNSSndSeqPlayer;

typedef struct NNSSndPlayer {
    NNSFndList playerList;
    NNSFndList heapList;
    u32 playableSeqCount;
    u32 allocatableChannelMask;
    u8 volume;
    u8 padding[3];
} NNSSndPlayer;

typedef struct NNSSndPlayerHeap {
    NNSFndLink link;
    NNSSndHeapHandle handle;
    NNSSndSeqPlayer *player;
    int playerNo;
} NNSSndPlayerHeap;

#define NNS_SND_HEAP_INVALID_HANDLE ((NNSSndHeapHandle)NULL)

static inline BOOL NNS_SndHandleIsValid(const NNSSndHandle *handle)
{
    return handle->player != NULL;
}

#endif
