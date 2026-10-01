typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct CARDRomHeader {
    u8 reserved000[0x80];
    u32 romSize;
} CARDRomHeader;

typedef int (*CARDReadRomFunction)(void *argument, void *buffer, u32 offset, u32 length);

typedef struct CARDRomState {
    u32 romBase;
    u8 reserved004[8];
    CARDReadRomFunction readRom;
} CARDRomState;

#define OS_BOOTTYPE_ROM 1
#define CARD_ROM_DOWNLOAD_SIGNATURE_SIZE 0x88

extern CARDRomState sCardRomState;
extern u8 CARDiOwnSignature[CARD_ROM_DOWNLOAD_SIGNATURE_SIZE];
extern int OS_GetBootType(void);
extern const CARDRomHeader *CARD_GetOwnRomHeader(void);
extern int OS_GetLockID(void);
extern void CARD_LockRom(u16 lockId);
extern int CARDi_ReadRomWithCPU(void *argument, void *buffer, u32 offset, u32 length);
extern void CARD_UnlockRom(u16 lockId);
extern void OS_ReleaseLockID(u16 lockId);

void CARDi_InitRom(void)
{
    sCardRomState.readRom = CARDi_ReadRomWithCPU;

    if (OS_GetBootType() == OS_BOOTTYPE_ROM &&
        CARD_GetOwnRomHeader()->romSize != 0) {
        u16 lockId = (u16)OS_GetLockID();

        CARD_LockRom(lockId);
        (void)CARDi_ReadRomWithCPU(0, CARDiOwnSignature,
                                   CARD_GetOwnRomHeader()->romSize,
                                   CARD_ROM_DOWNLOAD_SIGNATURE_SIZE);
        CARD_UnlockRom(lockId);
        OS_ReleaseLockID(lockId);
    }
}