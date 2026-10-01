typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long u32;
typedef signed long s32;
typedef volatile u8 REGType8v;
typedef volatile u16 REGType16v;
typedef volatile u32 REGType32v;
typedef volatile s32 vs32;
typedef int BOOL;

#define NULL ((void *)0)
#define CARD_ROM_PAGE_SIZE 0x200
#define MI_DMA_NOT_USE 0xffffffff
#define CARDMST_ENABLE 0x80
#define CARD_DATA_READY 0x00800000
#define CARD_COMMAND_PAGE 0x01000000
#define CARD_COMMAND_MASK 0x07000000
#define CARD_RESET_HI 0x20000000
#define CARD_READ_MODE 0
#define CARD_START 0x80000000
#define MROMOP_G_READ_PAGE 0xb7000000
#define HW_REG_BASE 0x04000000
#define REG_EXMEMCNT_OFFSET 0x204
#define reg_MI_EXMEMCNT (*(REGType16v *)(HW_REG_BASE + REG_EXMEMCNT_OFFSET))
#define REG_MI_EXMEMCNT_MP_MASK 0x800
#define REG_A9ROM_OFFSET 0x4000
#define REG_SCFG_A9ROM_SEC_MASK 1
#define PRIME_TRUE 251
#define PRIME_FALSE 241
#define PRIME_ROM_TEST_1 179
#define PRIME_ROM_TEST_2 191

extern s32 OS_GetLockID(void);
extern void OS_ReleaseLockID(u16 lock_id);
extern void ROMTest_IsBad_CARD_LockRom_Thunk(u16 lock_id);
extern void ROMTest_IsBad_CARD_UnlockRom_Thunk(u16 lock_id);
extern void ROMTest_IsBad_CARDi_ReadRom_Thunk(u32 dma, const void *src, void *dst, u32 len, void *callback, void *arg, BOOL is_async);
extern void ROMTest_IsGood_CARD_LockRom_Thunk(u16 lock_id);
extern void ROMTest_IsGood_CARD_UnlockRom_Thunk(u16 lock_id);
extern void ROMTest_IsGood_CARDi_ReadRom_Thunk(u32 dma, const void *src, void *dst, u32 len, void *callback, void *arg, BOOL is_async);
extern u32 RunEncrypted_ROMUtil_CRC32(void *buf, u32 size);

#ifdef ROM_TEST_GOOD
#define CARD_LockRom ROMTest_IsGood_CARD_LockRom_Thunk
#define CARD_UnlockRom ROMTest_IsGood_CARD_UnlockRom_Thunk
#define CARDi_ReadRom ROMTest_IsGood_CARDi_ReadRom_Thunk
#else
#define CARD_LockRom ROMTest_IsBad_CARD_LockRom_Thunk
#define CARD_UnlockRom ROMTest_IsBad_CARD_UnlockRom_Thunk
#define CARDi_ReadRom ROMTest_IsBad_CARDi_ReadRom_Thunk
#endif
static inline void CARD_ReadRom(u32 dma, const void *src, void *dst, u32 len) {
    CARDi_ReadRom(dma, src, dst, len, NULL, NULL, 0);
}