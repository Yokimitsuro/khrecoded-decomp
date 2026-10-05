#include "nitro/types.h"

extern void *gPanelState;
extern void func_020284d0(void *entry);
extern void SoundMgr_Update(void);

void func_020281c8(void) {
    func_020284d0((u8 *)gPanelState + 0xc);
    SoundMgr_Update();
}
