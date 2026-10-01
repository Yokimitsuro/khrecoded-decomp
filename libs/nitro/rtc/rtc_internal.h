#ifndef NITRO_RTC_INTERNAL_H
#define NITRO_RTC_INTERNAL_H

typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef u32 OSIntrMode;
typedef int BOOL;
typedef int RTCResult;
typedef int RTCWeek;
typedef void (*RTCCallback)(RTCResult result, void *argument);
typedef void (*RTCInterrupt)(void);

typedef struct RTCDate {
    u32 year;
    u32 month;
    u32 day;
    RTCWeek week;
} RTCDate;

typedef struct RTCTime {
    u32 hour;
    u32 minute;
    u32 second;
} RTCTime;

typedef struct RTCWork {
    u32 lock;
    RTCCallback callback;
    void *buffer[2];
    void *callbackArg;
    u32 sequence;
    u32 index;
    RTCInterrupt interrupt;
    RTCResult commonResult;
} RTCWork;

typedef struct RTCBss {
    u16 initialized;
    u16 padding;
    RTCWork work;
} RTCBss;

enum RTCLock {
    RTC_LOCK_OFF = 0,
    RTC_LOCK_ON = 1
};

enum RTCSequence {
    RTC_SEQ_GET_DATE = 0,
    RTC_SEQ_GET_TIME,
    RTC_SEQ_GET_DATETIME
};

enum RTCResultValue {
    RTC_RESULT_SUCCESS = 0,
    RTC_RESULT_BUSY = 1,
    RTC_RESULT_SEND_ERROR = 3
};

#define FALSE 0
#define TRUE 1
#define NULL 0
#define PXI_FIFO_TAG_RTC 5
#define PXI_PROC_ARM7 1
#define RTC_PXI_COMMAND_MASK 0x7f00
#define RTC_PXI_COMMAND_SHIFT 8
#define RTC_PXI_COMMAND_READ_DATETIME 0x10
#define RTC_PXI_COMMAND_READ_DATE 0x11
#define RTC_PXI_COMMAND_READ_TIME 0x12
#define RTC_PXI_COMMAND_WRITE_STATUS2 0x27

extern RTCBss RTCi_Bss;
extern volatile u32 RTCi_Lock;

void RTC_Init(void);
RTCResult RTC_GetDateAsync(RTCDate *date, RTCCallback callback, void *argument);
RTCResult RTC_GetDate(RTCDate *date);
RTCResult RTC_GetTimeAsync(RTCTime *time, RTCCallback callback, void *argument);
RTCResult RTC_GetTime(RTCTime *time);
RTCResult RTC_GetDateTimeAsync(
    RTCDate *date,
    RTCTime *time,
    RTCCallback callback,
    void *argument);
RTCResult RTC_GetDateTime(RTCDate *date, RTCTime *time);
RTCWeek RTC_GetDayOfWeek(RTCDate *date);

void RtcCommonCallback(int tag, u32 data, BOOL error);
u32 RtcBCD2HEX(u32 bcd);
void RtcGetResultCallback(RTCResult result, void *argument);
void RtcWaitBusy(void);
BOOL RtcSendPxiCommand(u32 command);
BOOL RTCi_ReadRawDateTimeAsync(void);
BOOL RTCi_ReadRawDateAsync(void);
BOOL RTCi_ReadRawTimeAsync(void);
BOOL RTCi_WriteRawStatus2Async(void);

#endif
