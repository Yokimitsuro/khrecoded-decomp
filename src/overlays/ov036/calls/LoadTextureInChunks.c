#include "nitro/types.h"

typedef struct SceneWork {
    u8 pad_0000[0x8];
    s32 state;
} SceneWork;

typedef struct SceneContext {
    u32 unk_00;
    SceneWork *work;
} SceneContext;

extern SceneContext data_ov036_020c3940;
extern BOOL IsSoundStreamActive(int channel);
extern void OS_WaitVBlankIntr(void);
extern void GX_BeginLoadTex(void);
extern void GX_LoadTex(const void *src, u32 destSlotAddr, u32 size);
extern void GX_EndLoadTex(void);

void LoadTextureInChunks(const u8 *src, u32 destSlotAddr, u32 size)
{
    int chunk = 0x8000;
    u32 i;
    u32 count;

    if (IsSoundStreamActive(0) || data_ov036_020c3940.work->state == 4) {
        chunk >>= 1;
        OS_WaitVBlankIntr();
    }
    if (size <= chunk) {
        GX_BeginLoadTex();
        GX_LoadTex(src, destSlotAddr, size);
        GX_EndLoadTex();
        return;
    }
    i = 0;
    count = size / chunk + 1;
    for (; i < count; i++) {
        GX_BeginLoadTex();
        GX_LoadTex(src + i * chunk, destSlotAddr + i * chunk, size > chunk ? chunk : size);
        size -= chunk;
        GX_EndLoadTex();
        if (size == 0) {
            return;
        }
        OS_WaitVBlankIntr();
    }
}
