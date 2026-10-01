#ifndef NITRO_SPI_PM_POWER_INTERNAL_H
#define NITRO_SPI_PM_POWER_INTERNAL_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int BOOL;
typedef u32 OSIntrMode;
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

typedef enum PMLEDStatus {
    PM_LED_NONE = 0,
    PM_LED_ON = 1,
    PM_LED_BLINK_LOW = 2,
    PM_LED_BLINK_HIGH = 3
} PMLEDStatus;

typedef enum PMAmpSwitch {
    PM_AMP_OFF = 0,
    PM_AMP_ON = 1
} PMAmpSwitch;

typedef struct PMWork {
    BOOL lock;
    PMCallback callback;
    void *callbackArgument;
    u16 *work;
} PMWork;

typedef struct PMiBssLayout {
    u16 isInitialized;
    u16 padding;
    u32 lcdCount;
    u32 displayOffCount;
    BOOL sleepEndFlag;
    void *preSleepCallbackList;
    void *reservedCallbackList;
    void *postSleepCallbackList;
    u32 preDmaCount[4];
    PMWork work;
} PMiBssLayout;

enum PMiWaitBusyMethod {
    PMi_WAITBUSY_METHOD_CPUMODE = 2,
    PMi_WAITBUSY_METHOD_CPSR = 4,
    PMi_WAITBUSY_METHOD_IME = 8
};

enum PMiPxiCommand {
    SPI_PXI_COMMAND_PM_SYNC = 0x60,
    SPI_PXI_COMMAND_PM_UTILITY = 0x61,
    SPI_PXI_COMMAND_PM_SLEEP_START = 0x62,
    SPI_PXI_COMMAND_PM_SLEEP_END = 0x63
};

#define SPI_PXI_RESULT_COMMAND_MASK 0x00007f00
#define SPI_PXI_RESULT_COMMAND_SHIFT 8
#define SPI_PXI_RESULT_DATA_MASK 0x000000ff
enum PMUtilityCommand {
    PM_UTIL_LED_ON = 1,
    PM_UTIL_LED_BLINK_HIGH_SPEED = 2,
    PM_UTIL_LED_BLINK_LOW_SPEED = 3,
    PM_UTIL_LCD1_BACKLIGHT_ON = 4,
    PM_UTIL_LCD1_BACKLIGHT_OFF = 5,
    PM_UTIL_LCD2_BACKLIGHT_ON = 6,
    PM_UTIL_LCD2_BACKLIGHT_OFF = 7,
    PM_UTIL_LCD12_BACKLIGHT_ON = 8,
    PM_UTIL_LCD12_BACKLIGHT_OFF = 9,
    PM_UTIL_FORCE_POWER_OFF = 14,
    PM_UTIL_GET_STATUS = 15,
    PM_UTIL_SET_AMP = 16
};

enum PMUtilityParameter {
    PM_UTIL_PARAM_BACKLIGHT = 3
};

#define FALSE 0
#define TRUE 1
#define PM_SUCCESS 0
#define PM_BUSY 1
#define PM_ERROR 2
#define PM_INVALID_COMMAND 0xffff
#define PMi_UNUSED_RESULT 0xffff0000
#define PMi_LCD_WAIT_SYS_CYCLES 0x360000
#define PMi_ARM9_CLOCK_DIV_100 335139
#define PMi_PXI_WAIT_TICK 5
#define PXI_FIFO_TAG_PM 8
#define PXI_PROC_ARM7 1
#define PXI_FIFO_SUCCESS 0
#define PMi_PXI_SYNC_PACKET 0x03006000
#define PMi_PXI_SLEEP_HEADER 0x02006200
#define PMi_PXI_UTILITY_HEADER 0x02006100
#define PMi_PXI_PARAMETER_HEADER 0x01010000
#define OS_VBLANK_COUNT (*(volatile u32 *)0x02fffc3c)

extern PMiBssLayout PMi_Bss;
extern PMWork PMi_Work;
extern u32 PMi_PreDmaCnt[4];
extern int PMi_WaitBusyMethod;

OSIntrMode OS_DisableInterrupts(void);
OSIntrMode OS_RestoreInterrupts(OSIntrMode mode);
void OS_SpinWait(u32 cycles);
void OS_Halt(void);
void MI_StopAllDma(void);
int PXI_SendWordByFifo(int tag, u32 data, BOOL error);
void PXI_Init(void);
BOOL PXI_IsCallbackReady(int tag, int processor);
void PXI_SetFifoRecvCallback(
    int tag,
    void (*callback)(int tag, u32 data, BOOL error));
void WaitByLoop(int count);

void PM_Init(void);
void PMi_CommonCallback(int tag, u32 data, BOOL error);
void PMi_WaitBusy(void);
void PMi_DummyCallback(u32 result, void *argument);
void PMi_CallCallbackAndUnlock(u32 result);
void PMi_LCDOnAvoidReset(void);
void PMi_SendPxiData(u32 data);
u32 PMi_TryToSendPxiData(
    u32 *sendData,
    int count,
    u16 *returnValue,
    PMCallback callback,
    void *argument);
void PMi_TryToSendPxiDataTillSuccess(u32 *sendData, int count);
u32 PMi_SendSleepStart(u16 trigger, u16 keyInterruptData);
void PMi_SetDispOffCount(void);

u32 PM_SendUtilityCommandAsync(
    u32 number,
    u16 parameter,
    u16 *returnValue,
    PMCallback callback,
    void *argument);
u32 PM_SendUtilityCommand(u32 number, u16 parameter, u16 *returnValue);
u32 PMi_SetLEDAsync(PMLEDStatus status, PMCallback callback, void *argument);
u32 PMi_SetLED(PMLEDStatus status);
u32 PM_SetBackLightAsync(
    PMLCDTarget target,
    PMBackLightSwitch state,
    PMCallback callback,
    void *argument);
u32 PM_SetBackLight(PMLCDTarget target, PMBackLightSwitch state);
u32 PM_ForceToPowerOffAsync(PMCallback callback, void *argument);
u32 PM_ForceToPowerOff(void);
u32 PMi_ForceToPowerOff(void);
u32 PMi_SetAmp(PMAmpSwitch status);
u32 PM_GetBackLight(PMBackLightSwitch *top, PMBackLightSwitch *bottom);
PMLCDPower PM_GetLCDPower(void);
BOOL PMi_SetLCDPower(
    PMLCDPower power,
    PMLEDStatus led,
    BOOL skip,
    BOOL synchronous);
BOOL PM_SetLCDPower(PMLCDPower power);

#endif
