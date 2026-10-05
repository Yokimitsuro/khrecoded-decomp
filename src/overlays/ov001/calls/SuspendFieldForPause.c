#include "nitro/types.h"

#define reg_OS_IME (*(vu16 *)0x04000208)

typedef struct {
    u8 data[0x1C];
} TickTween;

typedef struct {
    u8 pad_000[0x1C];
    u8 records[0x420];
    void *savedBgScreen;
    void *savedBg2Char;
    void *savedBgPalette;
    u8 pad_448[0x38];
    u32 isSliding : 1;
    u32 unk_480_1 : 3;
    u32 isPaused : 1;
    u32 unk_480_5 : 4;
    u32 showSlotRecords : 1;
    u8 pad_484[0xD0];
    TickTween tickerTween;
    u8 pad_570[0x6C];
    TickTween slideTween;
    void *slotRecords[3];
} FieldManager;

typedef struct {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

extern u64 OS_GetTick(void);
extern BOOL func_ov001_02072040(void);
extern void setStopwatchHeld(TickTween *tween, int hold);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8288(void *pool, void *record);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void *G2_GetBG2CharPtr(void);
extern void SetFieldMenuSuspended(int enable, int arg1);
extern void RefreshModeWindow(int arg0);

static inline u16 DisableIme(void)
{
    u16 prev = reg_OS_IME;
    reg_OS_IME = 0;
    return prev;
}

static inline u16 EnableIme(void)
{
    u16 prev = reg_OS_IME;
    reg_OS_IME = 1;
    return prev;
}

static inline void CopyBlock(const void *src, void *dst, u32 size)
{
    MIi_CpuCopyFast(src, dst, size);
}

void SuspendFieldForPause(void)
{
    FieldManager *manager = data_ov001_020a04c4.manager;
    BOOL overridden;
    u16 savedIme;
    int i;

    OS_GetTick();
    overridden = func_ov001_02072040();
    setStopwatchHeld(&manager->tickerTween, 1);
    setStopwatchHeld(&manager->slideTween, 1);
    if (manager->showSlotRecords) {
        func_ov027_020b8288(manager->records, FindActiveRecordById(manager->records, 0x52));
        for (i = 0; i < 3; i++) {
            manager->slotRecords[i] = NULL;
        }
    }
    savedIme = DisableIme();
    manager->savedBgScreen = NNS_FndAllocFromDefaultExpHeapEx(0x5C00, -0x20);
    CopyBlock((void *)0x06000000, manager->savedBgScreen, 0x5C00);
    manager->savedBg2Char = NNS_FndAllocFromDefaultExpHeapEx(0x1000, -0x20);
    CopyBlock(G2_GetBG2CharPtr(), manager->savedBg2Char, 0x1000);
    manager->savedBgPalette = NNS_FndAllocFromDefaultExpHeapEx(0x200, -0x20);
    CopyBlock((void *)0x05000000, manager->savedBgPalette, 0x200);
    if (savedIme) {
        EnableIme();
    }
    SetFieldMenuSuspended(1, overridden == FALSE);
    RefreshModeWindow(1);
}
