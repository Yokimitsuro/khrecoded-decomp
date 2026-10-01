#ifndef NITRO_OS_SYSTEM_WORK_INTERNAL_H
#define NITRO_OS_SYSTEM_WORK_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

typedef u16 OSBootType;

enum {
    OS_BOOTTYPE_ILLEGAL = 0,
    OS_BOOTTYPE_ROM = 1,
    OS_BOOTTYPE_DOWNLOAD_MB = 2,
    OS_BOOTTYPE_NAND = 3,
    OS_BOOTTYPE_MEMORY = 4
};

typedef struct OSBootInfo {
    OSBootType bootType;
    u16 length;
    u16 rssi;
    u16 bssid[3];
    u16 ssidLength;
    u8 ssid[32];
    u16 capabilityInfo;
    struct {
        u16 basic;
        u16 supported;
    } rateSet;
    u16 beaconPeriod;
    u16 dtimPeriod;
    u16 channel;
    u16 cfpPeriod;
    u16 cfpMaxDuration;
    u16 reserved;
} OSBootInfo;

#define HW_WM_BOOT_BUF ((const OSBootInfo *)0x02fffc40)

OSBootType OS_GetBootType(void);
const OSBootInfo *OS_GetBootInfo(void);

#endif