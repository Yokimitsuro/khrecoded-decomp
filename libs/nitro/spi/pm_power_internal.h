#ifndef NITRO_SPI_PM_POWER_INTERNAL_H
#define NITRO_SPI_PM_POWER_INTERNAL_H

typedef unsigned int u32;
typedef int BOOL;
typedef void (*PMCallback)(u32 result, void *argument);

typedef enum PMLCDTarget {
    PM_LCD_TOP = 0,
    PM_LCD_BOTTOM = 1,
    PM_LCD_ALL = 2
} PMLCDTarget;

typedef enum PMBackLightSwitch {
    PM_BACKLIGHT_OFF = 0,
    PM_BACKLIGHT_ON = 1
} PMBackLightSwitch;

typedef enum PMLCDPower {
    PM_LCD_POWER_OFF = 0,
    PM_LCD_POWER_ON = 1
} PMLCDPower;

enum PMiWaitBusyMethod {
    PMi_WAITBUSY_METHOD_CPUMODE = 2,
    PMi_WAITBUSY_METHOD_CPSR = 4,
    PMi_WAITBUSY_METHOD_IME = 8
};

#define PM_SUCCESS 0
#define PMi_LCD_WAIT_SYS_CYCLES 0x360000
#define PMi_ARM9_CLOCK_DIV_100 335139
#define PMi_PXI_WAIT_TICK 5

extern int PMi_WaitBusyMethod;

void OS_SpinWait(u32 cycles);
void PMi_WaitBusy(void);
void PMi_DummyCallback(u32 result, void *argument);
u32 PM_SetBackLightAsync(
    PMLCDTarget target,
    PMBackLightSwitch state,
    PMCallback callback,
    void *argument);
u32 PM_SetBackLight(PMLCDTarget target, PMBackLightSwitch state);
PMLCDPower PM_GetLCDPower(void);
BOOL PM_SetLCDPower(PMLCDPower power);

#endif