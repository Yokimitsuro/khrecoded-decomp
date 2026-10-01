typedef int BOOL;

typedef struct CARDiCommon {
    void *command;
    volatile int flags;
} CARDiCommon;

enum {
    CARD_STAT_BUSY = 4
};

extern CARDiCommon cardi_common;

BOOL CARDi_TryWaitAsync(void)
{
    return !(cardi_common.flags & CARD_STAT_BUSY);
}