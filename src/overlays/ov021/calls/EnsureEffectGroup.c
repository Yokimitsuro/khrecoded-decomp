#include "nitro/types.h"

typedef struct EntryGroupDesc {
    int kind;
    u32 endKey;
    int param;
    u32 startKey;
    int extra;
} EntryGroupDesc;

typedef struct {
    u32 index;
    int param;
} EffectGroupDef;

typedef struct {
    EffectGroupDef defs[19];
} EffectGroupTable;

typedef struct {
    u8 pad_00[0x24];
    s16 groupIds[1];
} EffectOwner;

extern const EffectGroupTable data_ov021_020b508c;
extern void ZeroBytes0x14(EntryGroupDesc *desc);
extern int func_ov001_0206dba0(int clock);
extern s16 func_ov021_020a89c8(EntryGroupDesc *desc);

s16 *EnsureEffectGroup(EffectOwner *owner, int slot)
{
    EffectGroupTable table = data_ov021_020b508c;
    EntryGroupDesc desc;
    u32 index;

    if (owner->groupIds[slot] == -1) {
        ZeroBytes0x14(&desc);
        index = table.defs[slot].index;
        desc.startKey = ((func_ov001_0206dba0(3) + 0x8000U & 0xfffffc) << 7) | 0x80000000 | (index & 0x1ff);
        desc.endKey = ((func_ov001_0206dba0(3) + 0x8000U & 0xfffffc) << 7) | 0x80000000 | (index + 1 & 0x1ff);
        desc.param = table.defs[slot].param;
        owner->groupIds[slot] = func_ov021_020a89c8(&desc);
    }
    return &owner->groupIds[slot];
}
