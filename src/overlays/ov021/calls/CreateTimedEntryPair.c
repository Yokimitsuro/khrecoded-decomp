#include "nitro/types.h"

typedef struct EntryGroupDesc {
    int kind;
    u32 endKey;
    int param;
    u32 startKey;
    int extra;
} EntryGroupDesc;

extern void ZeroBytes0x14(EntryGroupDesc *desc);
extern int func_ov001_0206dba0(int clock);
extern void func_ov021_020a89c8(EntryGroupDesc *desc);

void CreateTimedEntryPair(int unused, u32 index, int param, int extra)
{
    EntryGroupDesc desc;

    ZeroBytes0x14(&desc);
    desc.startKey = ((func_ov001_0206dba0(3) + 0x8000U & 0xfffffc) << 7) | 0x80000000 | (index & 0x1ff);
    desc.endKey = ((func_ov001_0206dba0(3) + 0x8000U & 0xfffffc) << 7) | 0x80000000 | (index + 1 & 0x1ff);
    desc.param = param;
    desc.extra = extra;
    func_ov021_020a89c8(&desc);
}
