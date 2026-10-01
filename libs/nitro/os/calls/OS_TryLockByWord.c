typedef unsigned short u16;
typedef int s32;

typedef struct OSLockWord {
    volatile u16 lockFlag;
    volatile u16 ownerID;
    void *extension;
} OSLockWord;

extern s32 OSi_DoTryLockByWord(u16 lockID, OSLockWord *lockp,
                               void (*ctrlFuncp)(void), int disableFiq);

s32 OS_TryLockByWord(u16 lockID, OSLockWord *lockp,
                     void (*ctrlFuncp)(void))
{
    return OSi_DoTryLockByWord(lockID, lockp, ctrlFuncp, 0);
}