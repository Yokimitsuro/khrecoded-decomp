typedef unsigned long u32;

enum {
    OS_CONSOLE_DEV_CARD = 0x00020000,
    OS_CONSOLE_DEV_DOWNLOAD = 0x00004000,
    OS_CONSOLE_DEV_NAND = 0x00040000,
    OS_CONSOLE_DEV_MEMORY = 0x00008000
};

extern u32 OS_GetBootType(void);

static const u32 OSi_DeviceTypeTable[] = {
    0,
    OS_CONSOLE_DEV_CARD,
    OS_CONSOLE_DEV_DOWNLOAD,
    OS_CONSOLE_DEV_NAND,
    OS_CONSOLE_DEV_MEMORY
};

u32 OSi_DetectDeviceType(void)
{
    return OSi_DeviceTypeTable[OS_GetBootType()];
}