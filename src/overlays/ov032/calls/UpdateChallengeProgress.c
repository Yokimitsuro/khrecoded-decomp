#include "nitro/types.h"

typedef struct {
    int counterIndex[32];
} CounterIndexTable;

typedef struct {
    u32 year;
    u32 month;
    u32 day;
    u32 week;
} RtcDate;

typedef struct {
    u32 hour;
    u32 minute;
    u32 second;
} RtcTime;

typedef struct {
    u8 pad_00[0x24];
    int messageList[5];
    int elapsedFrames;
} SceneState;

typedef struct {
    u8 *context;
    SceneState *scene;
} Ov032Globals;

typedef struct {
    u8 pad_00[0xc];
    u16 goal;
    u8 pad_0e[0x15];
    s8 progress;
    u8 pad_24[2];
    s8 conditionType;
    u8 pad_27[0x51];
    BOOL succeeded;
} ConditionEntry;

extern const CounterIndexTable data_ov032_020bfef8;
extern Ov032Globals data_ov032_020c0080;
extern int func_ov001_02063b68(int index);
extern int _s32_div_f(int numerator, int denominator);
extern void UploadGroupMenuTiles(int arg);
extern int RTC_GetDate(RtcDate *date);
extern int RTC_GetTime(RtcTime *time);
extern void *func_ov027_020ba2c8(void *list, int index);
extern void ShowFieldPopupText(void *message, int duration);

void UpdateChallengeProgress(ConditionEntry *entry)
{
    RtcDate date;
    RtcTime time;
    CounterIndexTable counterIndices = data_ov032_020bfef8;
    int goal;
    int value;
    int type;

    if (entry->progress < 0) {
        return;
    }
    type = entry->conditionType;
    goal = entry->goal;
    if ((u8)(s8)(type - 8) <= 3) {
        goal *= 30;
    } else if (type == 2 || (u8)(s8)(type - 15) <= 2) {
        goal = 1;
    }
    switch (type) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 9:
    case 10:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
        value = func_ov001_02063b68(counterIndices.counterIndex[type]);
        if (value >= goal) {
            entry->progress = -1;
            entry->succeeded = entry->conditionType >= 15;
        } else {
            entry->progress = _s32_div_f(value * 100, goal);
        }
        break;
    case 0:
        value = func_ov001_02063b68(4) + func_ov001_02063b68(12);
        if (value >= 8) {
            entry->progress = -1;
            entry->succeeded = FALSE;
        } else {
            entry->progress = value * 100 / 8;
        }
        break;
    case 1:
        value = func_ov001_02063b68(3) + func_ov001_02063b68(12);
        if (value >= 8) {
            entry->progress = -1;
            entry->succeeded = FALSE;
        } else {
            entry->progress = value * 100 / 8;
        }
        break;
    case 11:
        if (func_ov001_02063b68(6) > 0) {
            UploadGroupMenuTiles(0);
            entry->progress = -1;
            entry->succeeded = TRUE;
            break;
        }
    case 8:
        value = data_ov032_020c0080.scene->elapsedFrames;
        if (value >= goal) {
            entry->progress = -1;
            entry->succeeded = FALSE;
        } else {
            entry->progress = _s32_div_f(value * 100, goal);
        }
        break;
    case 12:
        if (RTC_GetDate(&date) == 0 && date.week != 0 && date.week != 6) {
            entry->progress++;
            if (entry->progress >= 100) {
                entry->progress = -1;
                entry->succeeded = FALSE;
            }
        }
        break;
    case 13:
    case 14:
        if (RTC_GetTime(&time) == 0) {
            if ((entry->conditionType == 13 && (time.hour < 5 || time.hour > 16)) ||
                (entry->conditionType == 14 && time.hour >= 5 && time.hour <= 16)) {
                entry->progress++;
                if (entry->progress >= 100) {
                    entry->progress = -1;
                    entry->succeeded = FALSE;
                }
            }
        }
        break;
    }
    if (entry->progress < 0) {
        if (entry->succeeded) {
            ShowFieldPopupText(func_ov027_020ba2c8(&data_ov032_020c0080.scene->messageList, 0x2d), 2000);
            return;
        }
        ShowFieldPopupText(func_ov027_020ba2c8(&data_ov032_020c0080.scene->messageList, 0x2e), 2000);
    }
}
