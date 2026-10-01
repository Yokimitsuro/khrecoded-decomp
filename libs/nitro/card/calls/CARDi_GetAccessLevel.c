typedef enum OSBootType {
    OS_BOOTTYPE_UNKNOWN,
    OS_BOOTTYPE_ROM
} OSBootType;

typedef enum CARDAccessLevel {
    CARD_ACCESS_LEVEL_NONE = 0,
    CARD_ACCESS_LEVEL_BACKUP = 3,
    CARD_ACCESS_LEVEL_FULL = 7
} CARDAccessLevel;

extern OSBootType OS_GetBootType(void);

CARDAccessLevel CARDi_GetAccessLevel(void)
{
    if (OS_GetBootType() == OS_BOOTTYPE_ROM) {
        return CARD_ACCESS_LEVEL_FULL;
    }
    return CARD_ACCESS_LEVEL_BACKUP;
}