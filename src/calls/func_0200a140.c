typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

typedef s32 CARDiOwner;
typedef enum { CARD_TARGET_NONE, CARD_TARGET_ROM, CARD_TARGET_BACKUP } CARDTargetMode;
#define CARD_RESULT_SUCCESS 0
#define OS_LOCK_ID_ERROR (-3)
#define CARD_ROM_PAGE_SIZE 512

typedef struct OSThreadQueue {
    struct OSThread *head;
    struct OSThread *tail;
} OSThreadQueue;

typedef struct CARDiCommandArg {
    int result;
    int type;
    u32 id;
    u32 src;
    u32 dst;
    u32 len;
} CARDiCommandArg;

typedef struct CARDiCommon {
    CARDiCommandArg *cmd;
    int command;
    volatile CARDiOwner lock_owner;
    volatile int lock_ref;
    OSThreadQueue lock_queue[1];
    CARDTargetMode lock_target;
    u32 src;
    u32 dst;
    u32 len;
    u32 dma;
} CARDiCommon;

typedef struct CARDRomStat {
    void (*read_func)(struct CARDRomStat *);
    u32 ctrl;
    u8 *cache_page;
    u32 dummy[5];
    u8 cache_buf[CARD_ROM_PAGE_SIZE];
} CARDRomStat;

#define REG_CARDCNT            0x040001a4
#define REG_CARD_DATA          0x04100010
#define CARD_DATA_READY         0x00800000
#define CARD_COMMAND_PAGE       0x01000000
#define CARD_COMMAND_ID         0x07000000
#define CARD_COMMAND_MASK       0x07000000
#define CARD_RESET_HI           0x20000000
#define CARD_READ_MODE          0x00000000
#define CARD_START              0x80000000
#define CARD_LATENCY1_MASK      0x00001FFF
#define MROMOP_G_READ_ID        0xB8000000
#define MROMOP_G_READ_PAGE      0xB7000000

extern u32 data_020423e8;
#define cardi_common data_020464e0
#define rom_stat data_02046b20
#define cardi_rom_header_addr data_020423e8
#define CARD_ALIGN_HI_BIT(n)     (((u32)(n)) & ~(CARD_ROM_PAGE_SIZE - 1))

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void func_02001f10(OSThreadQueue *queue);
#define OS_SleepThread func_02001f10
extern void OS_WakeupThread(OSThreadQueue *queue);
extern void OS_Terminate(void);
#define OS_Panic(...) OS_Terminate()
#define OS_TPanic(...) OS_Terminate()
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void MIi_CardDmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size);
extern void CARDi_SetRomOp(u32 cmd1, u32 cmd2);

static inline u32 CARDi_GetRomFlag(u32 flag)
{
    const u32 rom_ctrl = *(vu32 *)(cardi_rom_header_addr + 0x60);
    return (u32)((rom_ctrl & ~CARD_COMMAND_MASK) | flag |
                 CARD_READ_MODE | CARD_START | CARD_RESET_HI);
}

static inline void CARDi_SetRomOpReadPage1(u32 src)
{
    CARDi_SetRomOp((u32)(MROMOP_G_READ_PAGE | (src >> 8)), (u32)(src << 24));
}

extern CARDiCommon data_020464e0;
#define PXI_FIFO_TAG_CARD 14
#define PXI_FIFO_SUCCESS 0
extern int PXI_SendWordByFifo(int tag, u32 data, BOOL err);
extern void WaitByLoop(s32 count);

void func_0200a140(u32 data, u32 wait)
{
    while (PXI_SendWordByFifo(PXI_FIFO_TAG_CARD, data, FALSE) != PXI_FIFO_SUCCESS) {
        WaitByLoop((s32)wait);
    }
}
