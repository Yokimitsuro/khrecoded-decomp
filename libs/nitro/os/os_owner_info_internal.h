#ifndef NITRO_OS_OWNER_INFO_INTERNAL_H
#define NITRO_OS_OWNER_INFO_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

typedef struct OSBirthday {
    u8 month;
    u8 day;
} OSBirthday;

typedef struct OSOwnerInfo {
    u8 language;
    u8 favoriteColor;
    OSBirthday birthday;
    u16 nickname[11];
    u16 nicknameLength;
    u16 comment[27];
    u16 commentLength;
} OSOwnerInfo;

void OS_GetOwnerInfo(OSOwnerInfo *info);

#endif