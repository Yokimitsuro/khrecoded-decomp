typedef unsigned long u32;
typedef void (*OSIrqFunction)(void *arg);
typedef struct OSiIrqSlot {
    OSIrqFunction handler;
    u32 keepEnabled;
    void *argument;
} OSiIrqSlot;
extern OSiIrqSlot data_02056ae8[];
extern u32 OS_EnableIrqMask(u32 mask);
#define OSi_TimerSlots (&data_02056ae8[4])

void OSi_EnterTimerCallback(u32 timerNo, OSIrqFunction function, void *arg)
{
    OSi_TimerSlots[timerNo].handler = function;
    OSi_TimerSlots[timerNo].argument = arg;
    OS_EnableIrqMask(1 << (timerNo + 3));
    OSi_TimerSlots[timerNo].keepEnabled = 1;
}