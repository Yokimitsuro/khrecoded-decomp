#ifndef CARD_ROM_INTERNAL_H
#define CARD_ROM_INTERNAL_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed long s32;
typedef int BOOL;
typedef u32 OSIntrMode;
typedef volatile u16 vu16;
typedef volatile u32 vu32;

typedef struct OSThreadQueue {
    void *head;
    void *tail;
} OSThreadQueue;

typedef struct CARDTransferInfo {
    u32 command;
    void (*callback)(void *userdata);
    void *userdata;
    u32 src;
    u32 dst;
    u32 len;
    u32 work;
} CARDTransferInfo;

typedef struct CARDDmaInterface {
    void (*receive)(u32 channel, const void *source, void *destination, u32 length);
    void (*stop)(u32 channel);
} CARDDmaInterface;

typedef struct CARDBackupSpec {
    u32 totalSize;
    u32 sectorSize;
    u32 subSectorSize;
    u32 pageSize;
    u32 addressWidth;
    u32 programPageTime;
    u32 writePageTime;
    u32 writePageTotalTime;
    u32 eraseChipTime;
    u32 eraseChipTotalTime;
    u32 eraseSectorTime;
    u32 eraseSectorTotalTime;
    u32 eraseSubSectorTime;
    u32 eraseSubSectorTotalTime;
    u32 erasePageTime;
    u8 initialStatus;
    u8 padding0[3];
    u32 capabilities;
    u8 padding1[4];
} CARDBackupSpec;

typedef struct CARDiCommandArg {
    s32 result;
    u32 type;
    u32 cardId;
    u32 source;
    u32 destination;
    u32 length;
    CARDBackupSpec backup;
} CARDiCommandArg;

typedef struct CARDiCommon {
    CARDiCommandArg *command;
    volatile u32 flags;
    u32 priority;
    u32 instructionFlushThreshold;
    u32 dataFlushThreshold;
    volatile s32 lockOwner;
    int lockCount;
    OSThreadQueue lockQueue;
    int lockTarget;
    u8 threadContext[0xc0];
    u8 threadStack[0x400];
    void (*taskFunction)(struct CARDiCommon *common);
    void (*callback)(void *argument);
    void *callbackArgument;
    OSThreadQueue busyQueue;
    u32 source;
    u32 destination;
    u32 length;
    u32 dmaChannel;
    const CARDDmaInterface *dmaInterface;
    u32 requestType;
    int requestRetryCount;
    u32 requestMode;
    void *currentArm9Thread;
} CARDiCommon;

typedef int (*CARDReadRomFunction)(void *argument, void *buffer, u32 offset,
                                   u32 length);

typedef struct CARDRomState {
    u32 romBase;
    BOOL enableCacheInvalidationIC;
    CARDTransferInfo *dmaReadRegisteredInfo;
    CARDReadRomFunction readRom;
    CARDTransferInfo dmaReadInfo;
} CARDRomState;

typedef struct CARDRomConfig {
    u32 cachedPage;
    BOOL enableCacheInvalidationDC;
} CARDRomConfig;

extern CARDiCommon cardi_common;
extern CARDRomState sCardRomState;
extern CARDRomConfig sCardRomConfig;
extern CARDTransferInfo sCardDmaReadInfo;
extern u8 sCardRomCacheBuffer[0x200];
extern u8 sCardBackupCachePageBuffer[0x100];

#define REG_MCCNT0 (*(vu16 *)0x040001a0)
#define REG_MCCNT1 (*(vu32 *)0x040001a4)
#define REG_MCCMD0 (*(vu32 *)0x040001a8)
#define REG_MCCMD1 (*(vu32 *)0x040001ac)
#define REG_MCD1 (*(vu32 *)0x04100010)
#define CARD_ROM_CTRL (*(vu32 *)0x02fffae0)
#define CARD_BOOT_ID (*(vu32 *)0x02fffc00)

#define CARD_ROM_PAGE_SIZE 0x200
#define CARD_COMMAND_PAGE 0x01000000UL
#define CARD_COMMAND_ID 0x07000000UL
#define CARD_COMMAND_MASK 0x07000000UL
#define CARD_RESET_HI 0x20000000UL
#define CARD_START 0x80000000UL
#define CARD_DATA_READY 0x00800000UL
#define CARD_LATENCY1_MASK 0x00001fffUL
#define CARD_ROMST_RFS_WARN_L2_MASK 8
#define OS_IE_CARD_DATA 0x00080000UL
#define MI_DMA_MAX_NUM 3
#define HW_ITCM_SIZE 0x8000
#define HW_DTCM_SIZE 0x4000
#define OS_GetITCMAddress() ((void *)0x01ff8000)

#define CARDi_GetRomFlag(flag) \
    ((flag) | CARD_START | CARD_RESET_HI | \
     (CARD_ROM_CTRL & ~CARD_COMMAND_MASK))

#define MI_HToBE32(value) \
    ((((value) & 0xff000000UL) >> 24UL) | \
     (((value) & 0x00ff0000UL) >> 8UL) | \
     (((value) & 0x0000ff00UL) << 8UL) | \
     (((value) & 0x000000ffUL) << 24UL))

void CARDi_SetRomOp(u32 command, u32 offset);
void CARDi_StartRomPageTransfer(u32 offset);
u32 CARDi_ReadRomIDCore(void);
u32 CARDi_ReadRomStatusCore(void);
void CARDi_RefreshRom(u32 warningMask);
void CARDi_RefreshRomCore(void);
void CARDi_CheckPulledOutCore(u32 id);
void CARDi_EndTask(CARDiCommon *common);

#endif
