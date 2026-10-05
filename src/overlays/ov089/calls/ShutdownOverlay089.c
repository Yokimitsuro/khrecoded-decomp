#include "nitro/types.h"

extern void *func_ov039_020bc1dc(void);
extern void func_ov027_020b90b8(void *panel, u32 value);
extern void func_ov089_020bf4a8(void *menu);
extern void func_ov089_020bf970(void *menu);
extern void func_ov089_020bfaf0(void *menu);
extern void func_ov089_020bf37c(void *menu);
extern BOOL ReleaseRecordSlot(s32 slot);

void ShutdownOverlay089(void *menu)
{
    func_ov027_020b90b8(func_ov039_020bc1dc(), 0);
    func_ov089_020bf4a8(menu);
    func_ov089_020bf970(menu);
    func_ov089_020bfaf0(menu);
    func_ov089_020bf37c(menu);
    ReleaseRecordSlot(2);
}
