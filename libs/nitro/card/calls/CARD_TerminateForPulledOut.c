typedef unsigned short u16;
typedef unsigned long u32;

extern u32 PMi_ForceToPowerOff(void);
extern void CARDi_SendtoPxi(u32 data, u32 wait);
extern void MI_StopAllDma(void);
extern void OS_Terminate(void);

static inline int PAD_DetectFold(void)
{
    return (*(volatile u16 *)0x02ffffa8 & 0x8000) >> 15;
}

void CARD_TerminateForPulledOut(void)
{
    if (PAD_DetectFold()) {
        (void)PMi_ForceToPowerOff();
    }

    CARDi_SendtoPxi(1, 1);
    MI_StopAllDma();
    OS_Terminate();
}