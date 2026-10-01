typedef unsigned long u32;
typedef int BOOL;

typedef struct CARDPulledOutState {
    u32 slotResetCount;
    BOOL isPulledOut;
    BOOL (*userCallback)(void);
} CARDPulledOutState;

extern CARDPulledOutState sCardPullOutState;

BOOL CARD_IsPulledOut(void)
{
    return sCardPullOutState.isPulledOut;
}