typedef unsigned long u32;
typedef int BOOL;

typedef struct CARDPulledOutState {
    u32 slotResetCount;
    BOOL isPulledOut;
    BOOL (*userCallback)(void);
} CARDPulledOutState;

enum {
    CARD_PXI_COMMAND_RESET_SLOT = 2,
    CARD_PXI_COMMAND_PULLED_OUT = 0x11,
    CARD_PXI_COMMAND_MASK = 0x3f,
    CARD_EVENT_PULLED_OUT = 1,
    CARD_EVENT_SLOT_RESET = 2
};

extern CARDPulledOutState sCardPullOutState;
extern void CARDi_NotifyEvent(int event, void *argument);
extern void CARD_TerminateForPulledOut(void);
extern void OS_Terminate(void);

void CARDi_PulledOutCallback(int tag, u32 data, BOOL error)
{
    u32 command = data & CARD_PXI_COMMAND_MASK;

    if (command == CARD_PXI_COMMAND_PULLED_OUT) {
        if (sCardPullOutState.isPulledOut == 0) {
            BOOL terminateImmediately = 1;

            sCardPullOutState.isPulledOut = 1;
            CARDi_NotifyEvent(CARD_EVENT_PULLED_OUT, 0);

            if (sCardPullOutState.userCallback) {
                terminateImmediately = sCardPullOutState.userCallback();
            }

            if (terminateImmediately) {
                CARD_TerminateForPulledOut();
            }
        }
    } else if (command == CARD_PXI_COMMAND_RESET_SLOT) {
        sCardPullOutState.slotResetCount += 1;
        sCardPullOutState.isPulledOut = 0;
        CARDi_NotifyEvent(CARD_EVENT_SLOT_RESET, 0);
    } else {
        OS_Terminate();
    }
}
