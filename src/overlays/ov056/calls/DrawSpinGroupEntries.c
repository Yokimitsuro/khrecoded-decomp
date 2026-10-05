#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SpinEntry {
    u8 pad_000[2];
    s8 state;
    u8 pad_003[0x24 - 3];
    fx32 dirX;
    u8 pad_028[4];
    fx32 dirZ;
    u16 nodeFlags;
    u8 pad_032[0xac - 0x32];
    u16 angle;
    u8 pad_0ae[0x154 - 0xae];
} SpinEntry;

typedef struct SpinGroup {
    u8 pad_000[8];
    SpinEntry *entries;
    u8 pad_00c[0x15 - 0xc];
    u8 count;
    u8 pad_016[0x40 - 0x16];
    s8 flags;
    u8 pad_041[0x64 - 0x41];
    u8 model[0x190 - 0x64];
    u32 *matrix;
} SpinGroup;

extern unsigned short FX_Atan2Idx(int vertical, int horizontal);
extern void func_ov021_020ae8ac(u16 *node);
extern void NNS_G3dGlbFlushP(void);
extern void NNS_G3dGeBufferOP_N(u32 op, const u32 *args, u32 numWords);
extern void func_01ffe1bc(void *model);

void DrawSpinGroupEntries(SpinGroup *group)
{
    SpinEntry *entry;
    int i;
    for (i = 0; i < group->count; i++) {
        entry = &group->entries[i];
        if (entry->state != -1) {
            entry->angle = FX_Atan2Idx(entry->dirX, entry->dirZ);
            entry->nodeFlags |= 0x20;
            func_ov021_020ae8ac(&entry->nodeFlags);
        }
    }
    if (group->flags & 1) {
        NNS_G3dGlbFlushP();
        NNS_G3dGeBufferOP_N(0x17, group->matrix, 12);
        func_01ffe1bc(group->model);
    }
}
