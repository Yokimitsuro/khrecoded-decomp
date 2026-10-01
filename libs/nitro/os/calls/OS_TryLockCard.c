typedef unsigned short u16;
typedef int s32;

extern s32 OS_TryLockByWord(u16 lockID, void *lockp,
                            void (*ctrlFuncp)(void));
extern void OSi_AllocateCardBus(void);

s32 OS_TryLockCard(u16 lockID)
{
    return OS_TryLockByWord(lockID, (void *)0x02ffffe0, OSi_AllocateCardBus);
}