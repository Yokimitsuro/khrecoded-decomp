typedef unsigned long u32;

typedef struct CARDiCommon {
    void *command;
    volatile u32 flags;
    u32 priority;
    u32 instructionFlushThreshold;
    u32 dataFlushThreshold;
} CARDiCommon;

extern CARDiCommon cardi_common;

void CARD_SetCacheFlushThreshold(u32 instructionCache, u32 dataCache)
{
    cardi_common.instructionFlushThreshold = instructionCache;
    cardi_common.dataFlushThreshold = dataCache;
}