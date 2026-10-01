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

typedef struct OSSystemWork {
    u8 bootCheckInfo[0x20];
    u32 resetParameter;
    u8 resetSync[0x8];
    u32 romBaseOffset;
    u8 cartridgeModuleInfo[12];
    u32 vblankCount;
    u8 wmBootBuffer[0x40];
    u8 nvramUserInfo[0x100];
    u8 debuggerReserved1[0x20];
    u8 arenaInfo[0x48];
    u8 realTimeClock[8];
    u8 systemConfiguration[6];
    u8 printWindowMain;
    u8 printWindowSub;
    u8 printWindowMainError;
    u8 printWindowSubError;
    u8 reserved1fa[6];
    u8 romHeader[0x160];
    u8 debuggerReserved2[0x20];
    u32 pxiSignalParameter[2];
    u32 pxiHandlerInstalled[2];
    u32 micLastAddress;
    u16 micSamplingData;
    u16 wmCallbackControl;
    u16 wmRssiPool;
    u8 cartridgeModuleInfoSet;
    u8 cartridgePresent;
    u32 componentParameter;
    void *mainThreadInfo;
    void *subThreadInfo;
    u16 buttonXY;
    u8 touchPanel[4];
    u8 reserved3ae[0x52];
} OSSystemWork;

#define OS_SYSTEM_WORK ((OSSystemWork *)0x02fffc00)
#define HW_WM_BOOT_BUF ((const OSBootInfo *)0x02fffc40)

OSBootType OS_GetBootType(void);
const OSBootInfo *OS_GetBootInfo(void);

#endif
