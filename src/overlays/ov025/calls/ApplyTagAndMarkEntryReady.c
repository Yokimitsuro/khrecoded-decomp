#include "nitro/types.h"

extern u32 func_ov027_020ba1f8();
extern void SetupSlotListView(u32 entry, u32 tag, u32 field);
extern void func_ov027_020ba200(u32 owner, u32 flag);

void ApplyTagAndMarkEntryReady(u32 owner, u32 entry) {
    u32 tag = func_ov027_020ba1f8();
    SetupSlotListView(entry, tag, *(u32 *)(entry + 0xc));
    func_ov027_020ba200(owner, 1);
}
