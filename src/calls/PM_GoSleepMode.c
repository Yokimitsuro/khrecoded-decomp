#include "nitro/types.h"

typedef struct PMSleepCallbackInfo PMSleepCallbackInfo;

typedef struct PMSleepState {
    u8 pad_00[0xc];
    volatile BOOL sleepEndFlag;
    PMSleepCallbackInfo *preSleepList;
    u8 pad_14[4];
    PMSleepCallbackInfo *postSleepList;
} PMSleepState;

extern PMSleepState PMi_Bss;

extern u32 OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(u32 state);
extern u32 OS_DisableIrqMask(u32 mask);
extern u32 OS_SetIrqMask(u32 mask);
extern u32 OS_IsTickAvailable(void);
extern void OS_SpinWait(int cycles);
extern u16 OS_GetBootType(void);
extern BOOL CTRDG_IsExisting(void);
extern void OS_Halt(void);
extern void PMi_ExecuteList(PMSleepCallbackInfo *listp);
extern u32 PM_GetLCDPower(void);
extern u32 PM_GetBackLight(u32 *top, u32 *bottom);
extern u32 PM_SetBackLight(int target, int sw);
extern void PMi_WaitVBlank(void);
extern void func_02010638(void);
extern u32 PMi_SendSleepStart(u16 trigger, u16 keyIntrData);
extern BOOL PMi_SetLCDPower(int sw, int led, BOOL skip, BOOL isSync);
extern u32 PMi_SetLED(int status);
extern void PMi_ForceToPowerOff(void);

#define reg_OS_IME (*(volatile u16 *)0x04000208)
#define reg_OS_IF (*(volatile u32 *)0x04000214)
#define reg_GX_DISPCNT (*(volatile u32 *)0x04000000)
#define reg_GXS_DB_DISPCNT (*(volatile u32 *)0x04001000)

static inline BOOL OS_DisableIrq(void)
{
    u16 prep = reg_OS_IME;
    reg_OS_IME = 0;
    return (BOOL)prep;
}

static inline BOOL OS_EnableIrq(void)
{
    u16 prep = reg_OS_IME;
    reg_OS_IME = 1;
    return (BOOL)prep;
}

static inline BOOL OS_RestoreIrq(BOOL enable)
{
    u16 prep = reg_OS_IME;
    reg_OS_IME = (u16)enable;
    return (BOOL)prep;
}

static inline void GXS_DispOff(void)
{
    reg_GXS_DB_DISPCNT &= ~0x10000;
}

void PM_GoSleepMode(u32 trigger, u32 logic, u16 keyPattern)
{
    BOOL prepIrq;
    u32 prepIntrMode;
    u32 prepIntrMask;
    BOOL powerOffFlag = FALSE;
    u32 preTop;
    u32 preBottom;
    u32 preGX;
    u32 preGXS;
    u32 preLCDPower;
    u32 topRecover;
    u32 bottomRecover;

    PMi_ExecuteList(PMi_Bss.preSleepList);

    prepIrq = OS_DisableIrq();
    prepIntrMode = OS_DisableInterrupts();
    prepIntrMask = OS_DisableIrqMask(0x3fffff);

    {
        u32 intr = 0x40000 | (OS_IsTickAvailable() ? 8 : 0);
        OS_SetIrqMask(intr);
    }

    OS_RestoreInterrupts(prepIntrMode);
    OS_EnableIrq();

    if (trigger & 8) {
        u16 bootType = OS_GetBootType();
        if (bootType == 2 || bootType == 3) {
            trigger &= ~8;
        }
    }

    if (trigger & 0x10) {
        if (!CTRDG_IsExisting()) {
            trigger &= ~0x10;
        }
    }

    preGX = reg_GX_DISPCNT;
    preGXS = reg_GXS_DB_DISPCNT;
    preLCDPower = PM_GetLCDPower();

    while (PM_GetBackLight(&preTop, &preBottom) != 0) {
        OS_SpinWait(0x51d23);
    }

    while (PM_SetBackLight(2, 0) != 0) {
        OS_SpinWait(0x51d23);
    }

    PMi_WaitVBlank();
    reg_GX_DISPCNT = reg_GX_DISPCNT & ~0x30000;
    GXS_DispOff();
    PMi_WaitVBlank();
    PMi_WaitVBlank();

    func_02010638();

    PMi_Bss.sleepEndFlag = FALSE;
    bottomRecover = preBottom ? 0x80 : 0;
    topRecover = preTop ? 0x40 : 0;

    OS_SetIrqMask(0x40000);
    PMi_SendSleepStart((u16)(trigger | topRecover | bottomRecover), (u16)(logic | keyPattern));

    while (!PMi_Bss.sleepEndFlag) {
        OS_Halt();
    }

    {
        u32 intr = 0x40000 | (OS_IsTickAvailable() ? 8 : 0);
        OS_SetIrqMask(intr);
    }

    if ((trigger & 8) && (reg_OS_IF & 0x100000)) {
        powerOffFlag = TRUE;
    }

    if (!powerOffFlag) {
        if (preLCDPower == 1) {
            while (PMi_SetLCDPower(1, 1, TRUE, TRUE) != TRUE) {
            }
        } else {
            while (PMi_SetLED(1) != 0) {
                OS_SpinWait(0x51d23);
            }
        }

        reg_GX_DISPCNT = preGX;
        reg_GXS_DB_DISPCNT = preGXS;
    }

    OS_SpinWait(0x360000);

    OS_DisableIrq();
    OS_SetIrqMask(prepIntrMask);
    OS_RestoreInterrupts(prepIntrMode);
    OS_RestoreIrq(prepIrq);

    if (powerOffFlag) {
        PMi_ForceToPowerOff();
    }

    PMi_ExecuteList(PMi_Bss.postSleepList);
}
