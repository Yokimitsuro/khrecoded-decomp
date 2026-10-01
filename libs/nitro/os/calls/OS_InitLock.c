typedef unsigned long u32;
typedef unsigned short u16;

typedef struct OSLockWord {
    u32 lockFlag;
    u16 ownerID;
    u16 extension;
} OSLockWord;

#define HW_INIT_LOCK_BUF ((OSLockWord *)0x02fffff0)
#define HW_LOCK_ID_FLAG_MAIN ((u32 *)0x02ffffb0)
#define REG_EXMEMCNT (*(volatile u16 *)0x04000204)
#define OS_MAINP_SYSTEM_LOCK_ID 0x7f


extern void OS_LockByWord(u16 lockID, OSLockWord *lockp, void (*callback)(void));
extern void OS_UnlockByWord(u16 lockID, OSLockWord *lockp, void (*callback)(void));
extern void WaitByLoop(u32 count);
extern void MIi_CpuClear32(u32 value, void *destination, u32 size);

void OS_InitLock(void)
{
    static int isInitialized = 0;
    OSLockWord *lockp;

    if (isInitialized) {
        return;
    }
    isInitialized = 1;
    lockp = HW_INIT_LOCK_BUF;

    lockp->lockFlag = 0;
    OS_LockByWord(OS_MAINP_SYSTEM_LOCK_ID - 1, lockp, 0);

    while (lockp->extension != 0) {
        WaitByLoop(0x400);
    }

    HW_LOCK_ID_FLAG_MAIN[0] = 0xffffffff;
    HW_LOCK_ID_FLAG_MAIN[1] = 0xffff0000;
    MIi_CpuClear32(0, HW_LOCK_ID_FLAG_MAIN + 4, 0x28);

    REG_EXMEMCNT |= 0x800;
    REG_EXMEMCNT |= 0x80;

    OS_UnlockByWord(OS_MAINP_SYSTEM_LOCK_ID - 1, lockp, 0);
    OS_LockByWord(OS_MAINP_SYSTEM_LOCK_ID, lockp, 0);
}