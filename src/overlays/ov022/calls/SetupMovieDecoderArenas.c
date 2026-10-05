#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x48];
    void *codeBackup;
    u32 codeSize;
    void *codeAddress;
} MovieFileBank;

extern MovieFileBank data_ov022_020b7db4;

extern int func_ov022_020aa8c0(void);
extern u32 OS_GetArenaHi(int index);
extern u32 OS_GetArenaLo(int index);
extern u32 OS_GetDTCMAddress(void);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuCopy8(const void *src, void *dest, u32 size);
extern unsigned int func_ov022_020aa8cc(void);
extern void func_ov022_020aa8d4(void *arenaBase, unsigned int arenaSize);
extern void func_ov022_020aa8f4(void *arenaBase, unsigned int arenaSize);

void SetupMovieDecoderArenas(void) {
    MovieFileBank *bank = &data_ov022_020b7db4;
    u32 tableSize;
    u32 tableBase;

    bank->codeSize = func_ov022_020aa8c0();
    bank->codeAddress = (void *)(OS_GetArenaHi(3) - bank->codeSize);
    bank->codeBackup = NNSi_FndAllocFromDefaultHeap(bank->codeSize);
    MI_CpuCopy8(bank->codeAddress, bank->codeBackup, bank->codeSize);
    tableBase = OS_GetArenaLo(4);
    tableSize = OS_GetDTCMAddress() + 0x4000 - tableBase;
    if (tableSize >= func_ov022_020aa8cc()) {
        tableSize = func_ov022_020aa8cc();
    }
    func_ov022_020aa8d4(bank->codeAddress, bank->codeSize);
    func_ov022_020aa8f4((void *)OS_GetArenaLo(4), tableSize);
}
