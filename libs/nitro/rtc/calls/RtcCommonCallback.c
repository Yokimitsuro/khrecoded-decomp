#include "libs/nitro/rtc/rtc_internal.h"

void RtcCommonCallback (PXIFifoTag tag, u32 data, BOOL err)
{

    RTCResult result;
    RTCPxiResult pxiresult;
    u8 command;
    RTCCallback cb;

    if (err) {
        if (RTCi_Bss.work.index) {
            RTCi_Bss.work.index = 0;
        }

        if (RTCi_Bss.work.lock != RTC_LOCK_OFF) {
            RTCi_Bss.work.lock = RTC_LOCK_OFF;
        }

        if (RTCi_Bss.work.callback) {
            cb = RTCi_Bss.work.callback;
            RTCi_Bss.work.callback = NULL;
            cb(RTC_RESULT_FATAL_ERROR, RTCi_Bss.work.callbackArg);
        }

        return;
    }

    command = (u8)((data & RTC_PXI_COMMAND_MASK) >> RTC_PXI_COMMAND_SHIFT);
    pxiresult = (RTCPxiResult)((data & RTC_PXI_RESULT_MASK) >> RTC_PXI_RESULT_SHIFT);

    if (command == RTC_PXI_COMMAND_INTERRUPT) {
        if (RTCi_Bss.work.interrupt) {
            RTCi_Bss.work.interrupt();
        }
        return;
    }

    if (pxiresult == RTC_PXI_RESULT_SUCCESS) {
        result = RTC_RESULT_SUCCESS;
        switch (RTCi_Bss.work.sequence) {

        case RTC_SEQ_GET_DATE:
        {
            RTCDate * pDst = (RTCDate *)(RTCi_Bss.work.buffer[0]);
            RTCRawDate * pSrc = &(RTC_RAW_DATA->dateTime.date);

            pDst->year = RtcBCD2HEX(pSrc->year);
            pDst->month = RtcBCD2HEX(pSrc->month);
            pDst->day = RtcBCD2HEX(pSrc->day);
            pDst->week = RTC_GetDayOfWeek(pDst);
        }
        break;
        case RTC_SEQ_GET_TIME:
        {
            RTCTime * pDst = (RTCTime *)(RTCi_Bss.work.buffer[0]);
            RTCRawTime * pSrc = &(RTC_RAW_DATA->dateTime.time);

            pDst->hour = RtcBCD2HEX(pSrc->hour);
            pDst->minute = RtcBCD2HEX(pSrc->minute);
            pDst->second = RtcBCD2HEX(pSrc->second);
        }
        break;
        case RTC_SEQ_GET_DATETIME:
        {
            RTCDate * pDst = (RTCDate *)(RTCi_Bss.work.buffer[0]);
            RTCRawDate * pSrc = &(RTC_RAW_DATA->dateTime.date);

            pDst->year = RtcBCD2HEX(*(u32 *)pSrc & 0x000000ff);
            pDst->month = RtcBCD2HEX(pSrc->month);
            pDst->day = RtcBCD2HEX(pSrc->day);
            pDst->week = RTC_GetDayOfWeek(pDst);
        }
            {
                RTCTime * pDst = (RTCTime *)(RTCi_Bss.work.buffer[1]);
                RTCRawTime * pSrc = &(RTC_RAW_DATA->dateTime.time);

                pDst->hour = RtcBCD2HEX(pSrc->hour);
                pDst->minute = RtcBCD2HEX(pSrc->minute);
                pDst->second = RtcBCD2HEX(pSrc->second);
            }
            break;

        case RTC_SEQ_SET_DATE:
        case RTC_SEQ_SET_TIME:
        case RTC_SEQ_SET_DATETIME:
            break;
        case RTC_SEQ_GET_ALARM1_STATUS:
        {
            RTCAlarmStatus * pDst = (RTCAlarmStatus *)(RTCi_Bss.work.buffer[0]);
            RTCRawStatus2 * pSrc = &(RTC_RAW_DATA->alarmData.status2);

            switch (pSrc->interruptMode) {
            case RTC_INTERRUPT_MODE_ALARM:
                *pDst = RTC_ALARM_STATUS_ON;
                break;
            default:
                *pDst = RTC_ALARM_STATUS_OFF;
            }
        }
        break;

        case RTC_SEQ_GET_ALARM2_STATUS:
        {
            RTCAlarmStatus * pDst = (RTCAlarmStatus *)(RTCi_Bss.work.buffer[0]);
            RTCRawStatus2 * pSrc = &(RTC_RAW_DATA->alarmData.status2);

            if (pSrc->interrupt2Mode) {
                *pDst = RTC_ALARM_STATUS_ON;
            } else {
                *pDst = RTC_ALARM_STATUS_OFF;
            }
        }
        break;

        case RTC_SEQ_GET_ALARM_PARAM:
        {
            RTCAlarmParam * pDst = (RTCAlarmParam *)(RTCi_Bss.work.buffer[0]);
            RTCRawAlarm * pSrc = &(RTC_RAW_DATA->alarmData.registerData.alarm);

            pDst->week = (RTCWeek)(pSrc->week);
            pDst->hour = RtcBCD2HEX(pSrc->hour);
            pDst->minute = RtcBCD2HEX(pSrc->minute);
            pDst->enable = RTC_ALARM_ENABLE_NONE;
            if (pSrc->weekEnable)
                pDst->enable += RTC_ALARM_ENABLE_WEEK;
            if (pSrc->hourEnable)
                pDst->enable += RTC_ALARM_ENABLE_HOUR;
            if (pSrc->minuteEnable)
                pDst->enable += RTC_ALARM_ENABLE_MINUTE;
        }
        break;
        case RTC_SEQ_SET_ALARM1_STATUS:
            if (RTCi_Bss.work.index == 0) {
                RTCRawStatus2 * pSrc = &(RTC_RAW_DATA->alarmData.status2);

                if (*(RTCAlarmStatus *)(RTCi_Bss.work.buffer[0]) == RTC_ALARM_STATUS_ON) {
                    if (pSrc->interruptMode != RTC_INTERRUPT_MODE_ALARM) {
                        RTCi_Bss.work.index++;
                        pSrc->interruptMode = RTC_INTERRUPT_MODE_ALARM;
                        if (!RTCi_WriteRawStatus2Async()) {
                            RTCi_Bss.work.index = 0;
                            result = RTC_RESULT_SEND_ERROR;
                        }
                    }
                } else {
                    if (pSrc->interruptMode != RTC_INTERRUPT_MODE_NONE) {
                        RTCi_Bss.work.index++;
                        pSrc->interruptMode = RTC_INTERRUPT_MODE_NONE;
                        if (!RTCi_WriteRawStatus2Async()) {
                            RTCi_Bss.work.index = 0;
                            result = RTC_RESULT_SEND_ERROR;
                        }
                    }
                }
            } else {
                RTCi_Bss.work.index = 0;
            }
            break;
        case RTC_SEQ_SET_ALARM2_STATUS:
            if (RTCi_Bss.work.index == 0) {
                RTCRawStatus2 * pSrc = &(RTC_RAW_DATA->alarmData.status2);

                if (*(RTCAlarmStatus *)(RTCi_Bss.work.buffer[0]) == RTC_ALARM_STATUS_ON) {
                    if (!pSrc->interrupt2Mode) {
                        RTCi_Bss.work.index++;
                        pSrc->interrupt2Mode = 1;
                        if (!RTCi_WriteRawStatus2Async()) {
                            RTCi_Bss.work.index = 0;
                            result = RTC_RESULT_SEND_ERROR;
                        }
                    }
                } else {

                    if (pSrc->interrupt2Mode) {

                        RTCi_Bss.work.index++;
                        pSrc->interrupt2Mode = 0;
                        if (!RTCi_WriteRawStatus2Async()) {
                            RTCi_Bss.work.index = 0;
                            result = RTC_RESULT_SEND_ERROR;
                        }
                    }
                }
            } else {
                RTCi_Bss.work.index = 0;
            }
            break;
        case RTC_SEQ_SET_ALARM1_PARAM:
        case RTC_SEQ_SET_ALARM2_PARAM:
        case RTC_SEQ_SET_HOUR_FORMAT:
        case RTC_SEQ_SET_REG_STATUS2:
        case RTC_SEQ_SET_REG_ADJUST:
            break;
        default:
            result = RTC_RESULT_INVALID_COMMAND;
            RTCi_Bss.work.index = 0;
        }
    } else {
        RTCi_Bss.work.index = 0;

        switch (pxiresult) {
        case RTC_PXI_RESULT_INVALID_COMMAND:
            result = RTC_RESULT_INVALID_COMMAND;
            break;
        case RTC_PXI_RESULT_ILLEGAL_STATUS:
            result = RTC_RESULT_ILLEGAL_STATUS;
            break;
        case RTC_PXI_RESULT_BUSY:
            result = RTC_RESULT_BUSY;
            break;
        case RTC_PXI_RESULT_FATAL_ERROR:
        default:
            result = RTC_RESULT_FATAL_ERROR;
        }
    }

    if (RTCi_Bss.work.index == 0) {
        if (RTCi_Bss.work.lock != RTC_LOCK_OFF) {
            RTCi_Bss.work.lock = RTC_LOCK_OFF;
        }

        if (RTCi_Bss.work.callback) {
            cb = RTCi_Bss.work.callback;
            RTCi_Bss.work.callback = NULL;
            cb(result, RTCi_Bss.work.callbackArg);
        }
    }
}
