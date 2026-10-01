#include "libs/nitro/os/os_owner_info_internal.h"

typedef struct NVRAMConfig {
    u8 version;
    u8 padding;
    u8 favoriteColor : 4;
    u8 favoriteReserved : 4;
    u8 birthdayMonth;
    u8 birthdayDay;
    u8 ownerPadding;
    u16 nickname[10];
    u8 nicknameLength;
    u8 nicknameReserved;
    u16 comment[26];
    u8 commentLength;
    u8 commentReserved;
    u8 alarmAndCalibration[18];
    u16 language : 3;
    u16 optionReserved : 13;
} NVRAMConfig;

extern void MIi_CpuCopy16(const void *source, void *destination, u32 size);

void OS_GetOwnerInfo(OSOwnerInfo *info)
{
    NVRAMConfig *source = (NVRAMConfig *)0x02fffc80;

    info->language = source->language;
    info->favoriteColor = source->favoriteColor;
    info->birthday.month = source->birthdayMonth;
    info->birthday.day = source->birthdayDay;
    info->nicknameLength = source->nicknameLength;
    info->commentLength = source->commentLength;

    MIi_CpuCopy16(source->nickname, info->nickname, 20);
    MIi_CpuCopy16(source->comment, info->comment, 52);

    info->nickname[10] = 0;
    info->comment[26] = 0;
}