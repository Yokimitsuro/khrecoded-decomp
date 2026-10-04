#ifndef NITRO_SND_WORK_INTERNAL_H
#define NITRO_SND_WORK_INTERNAL_H

typedef signed short s16;
typedef unsigned short u16;
typedef unsigned long u32;

#define SND_PLAYER_COUNT 16
#define SND_PLAYER_VARIABLE_COUNT 16
#define SND_GLOBAL_VARIABLE_COUNT 16

typedef struct SNDSharedPlayerWork {
    volatile s16 variable[SND_PLAYER_VARIABLE_COUNT];
    volatile u32 tickCounter;
} SNDSharedPlayerWork;

typedef struct SNDSharedWork {
    volatile u32 finishCommandTag;
    volatile u32 playerStatus;
    volatile u16 channelStatus;
    volatile u16 captureStatus;
    volatile u32 padding[5];
    SNDSharedPlayerWork player[SND_PLAYER_COUNT];
    volatile s16 globalVariable[SND_GLOBAL_VARIABLE_COUNT];
} SNDSharedWork;

extern SNDSharedWork *SNDi_SharedWork;
extern void DC_InvalidateRange(void *address, u32 size);
extern void DC_FlushRange(const void *address, u32 size);

#endif
