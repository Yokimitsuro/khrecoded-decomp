#ifndef NITRO_RTC_INTERNAL_H
#define NITRO_RTC_INTERNAL_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef u32 OSIntrMode;
typedef int BOOL;
typedef int PXIFifoTag;
typedef int RTCResult;
typedef int RTCPxiResult;
typedef int RTCWeek;
typedef int RTCAlarmStatus;
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

typedef struct RTCAlarmParam {
    RTCWeek week;
    u32 hour;
    u32 minute;
    u32 enable;
} RTCAlarmParam;

typedef struct RTCRawDate {
    u32 year : 8;
    u32 month : 5;
    u32 dummy0 : 3;
    u32 day : 6;
    u32 dummy1 : 2;
    u32 week : 3;
    u32 dummy2 : 5;
} RTCRawDate;

typedef struct RTCRawTime {
    u32 hour : 6;
    u32 afternoon : 1;
    u32 dummy0 : 1;
    u32 minute : 7;
    u32 dummy1 : 1;
    u32 second : 7;
    u32 dummy2 : 9;
} RTCRawTime;

typedef struct RTCRawStatus1 {
    u16 reset : 1;
    u16 format : 1;
    u16 dummy0 : 2;
    u16 intr1 : 1;
    u16 intr2 : 1;
    u16 batteryLow : 1;
    u16 powerOnClear : 1;
    u16 dummy1 : 8;
} RTCRawStatus1;

typedef struct RTCRawStatus2 {
    u16 interruptMode : 4;
    u16 dummy0 : 2;
    u16 interrupt2Mode : 1;
    u16 test : 1;
    u16 dummy1 : 8;
} RTCRawStatus2;

typedef struct RTCRawAlarm {
    u32 week : 3;
    u32 dummy0 : 4;
    u32 weekEnable : 1;
    u32 hour : 6;
    u32 afternoon : 1;
    u32 hourEnable : 1;
    u32 minute : 7;
    u32 minuteEnable : 1;
    u32 dummy1 : 8;
} RTCRawAlarm;

typedef struct RTCRawPulse {
    u32 pulse : 5;
    u32 dummy : 27;
} RTCRawPulse;

typedef struct RTCRawAdjust {
    u32 adjust : 8;
    u32 dummy : 24;
} RTCRawAdjust;

typedef struct RTCRawFree {
    u32 free : 8;
    u32 dummy : 24;
} RTCRawFree;

typedef union RTCRawData {
    struct {
        RTCRawDate date;
        RTCRawTime time;
    } dateTime;
    struct {
        RTCRawStatus1 status1;
        RTCRawStatus2 status2;
        union {
            RTCRawPulse pulse;
            RTCRawAlarm alarm;
            RTCRawAdjust adjust;
            RTCRawFree free;
        } registerData;
    } alarmData;
    u32 words[2];
    u16 halfWords[4];
    u8 bytes[8];
} RTCRawData;

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
    RTC_SEQ_GET_DATETIME,
    RTC_SEQ_SET_DATE,
    RTC_SEQ_SET_TIME,
    RTC_SEQ_SET_DATETIME,
    RTC_SEQ_GET_ALARM1_STATUS,
    RTC_SEQ_GET_ALARM2_STATUS,
    RTC_SEQ_GET_ALARM_PARAM,
    RTC_SEQ_SET_ALARM1_STATUS,
    RTC_SEQ_SET_ALARM2_STATUS,
    RTC_SEQ_SET_ALARM1_PARAM,
    RTC_SEQ_SET_ALARM2_PARAM,
    RTC_SEQ_SET_HOUR_FORMAT,
    RTC_SEQ_SET_REG_STATUS2,
    RTC_SEQ_SET_REG_ADJUST
};

enum RTCResultValue {
    RTC_RESULT_SUCCESS = 0,
    RTC_RESULT_BUSY,
    RTC_RESULT_ILLEGAL_PARAMETER,
    RTC_RESULT_SEND_ERROR,
    RTC_RESULT_INVALID_COMMAND,
    RTC_RESULT_ILLEGAL_STATUS,
    RTC_RESULT_FATAL_ERROR
};

enum RTCPxiResultValue {
    RTC_PXI_RESULT_SUCCESS = 0,
    RTC_PXI_RESULT_INVALID_COMMAND,
    RTC_PXI_RESULT_ILLEGAL_STATUS,
    RTC_PXI_RESULT_BUSY,
    RTC_PXI_RESULT_FATAL_ERROR
};

enum RTCAlarmStatusValue {
    RTC_ALARM_STATUS_OFF = 0,
    RTC_ALARM_STATUS_ON
};

#define FALSE 0
#define TRUE 1
#define NULL 0
#define PXI_FIFO_TAG_RTC 5
#define PXI_PROC_ARM7 1
#define RTC_PXI_COMMAND_MASK 0x7f00
#define RTC_PXI_COMMAND_SHIFT 8
#define RTC_PXI_RESULT_MASK 0xff
#define RTC_PXI_RESULT_SHIFT 0
#define RTC_PXI_COMMAND_READ_DATETIME 0x10
#define RTC_PXI_COMMAND_READ_DATE 0x11
#define RTC_PXI_COMMAND_READ_TIME 0x12
#define RTC_PXI_COMMAND_WRITE_STATUS2 0x27
#define RTC_PXI_COMMAND_INTERRUPT 0x30
#define RTC_ALARM_ENABLE_NONE 0
#define RTC_ALARM_ENABLE_WEEK 1
#define RTC_ALARM_ENABLE_HOUR 2
#define RTC_ALARM_ENABLE_MINUTE 4
#define RTC_INTERRUPT_MODE_NONE 0
#define RTC_INTERRUPT_MODE_ALARM 4
#define RTC_RAW_DATA ((RTCRawData *)0x02fffde8)

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

void RtcCommonCallback(PXIFifoTag tag, u32 data, BOOL error);
u32 RtcBCD2HEX(u32 bcd);
void RtcGetResultCallback(RTCResult result, void *argument);
void RtcWaitBusy(void);
BOOL RtcSendPxiCommand(u32 command);
BOOL RTCi_ReadRawDateTimeAsync(void);
BOOL RTCi_ReadRawDateAsync(void);
BOOL RTCi_ReadRawTimeAsync(void);
BOOL RTCi_WriteRawStatus2Async(void);

#endif
