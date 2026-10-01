typedef unsigned long u32;
typedef int BOOL;

typedef struct CARDPulledOutState {
    u32 slotResetCount;
    BOOL isPulledOut;
    BOOL (*userCallback)(void);
} CARDPulledOutState;

extern CARDPulledOutState sCardPullOutState;
extern void PXI_Init(void);
extern void PXI_SetFifoRecvCallback(int tag, void (*callback)(int tag, u32 data, BOOL error));
extern void CARDi_PulledOutCallback(int tag, u32 data, BOOL error);

void CARD_InitPulledOutCallback(void)
{
    PXI_Init();

    sCardPullOutState.slotResetCount = 0;
    sCardPullOutState.isPulledOut = 0;
    PXI_SetFifoRecvCallback(14, CARDi_PulledOutCallback);
    sCardPullOutState.userCallback = 0;
}