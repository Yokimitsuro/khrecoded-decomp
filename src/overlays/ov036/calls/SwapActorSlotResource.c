#include "nitro/types.h"

typedef struct ActorSlotHeader {
    u8 pad_00[0x6];
    s16 height;
    u8 pad_08[0xc];
    s32 posY;
    u8 pad_18[0x8];
    u32 drawParam;
    u8 pad_24[0x2];
    u16 drawFlags;
    u8 pad_28[0x2];
    u8 priority : 5;
    u8 priorityPad : 3;
    u8 pad_2B[0x5];
} ActorSlotHeader;

typedef struct ActorSlot {
    ActorSlotHeader header;
    u8 pad_30[0x44];
    void *resource;
} ActorSlot;

typedef struct ActorSlotWork {
    u8 pad_0000[0xe7c];
    void *pendingResource;
} ActorSlotWork;

typedef struct ActorSlotContext {
    u32 unk_00;
    ActorSlotWork *work;
} ActorSlotContext;

typedef void (*TextureLoader)(const u8 *src, u32 destSlotAddr, u32 size);

extern ActorSlotContext data_ov036_020c3940;
extern TextureLoader data_02060570;
extern void LoadTextureInChunks(const u8 *src, u32 destSlotAddr, u32 size);
extern void *AcquireOrRefreshResourceBlock(void *resource, void *arg, int mode);
extern void func_0202c6a4(int mode);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void SetSlotKeyAndRebind(ActorSlot *slot, void *key, int flags);
extern void ReleaseResourceSlot(void *resource);
extern void ReleaseSharedRecordSlot(void *resource);
extern int func_ov036_020bb8ec(int height);

void SwapActorSlotResource(ActorSlot *slot)
{
    void *oldResource = slot->resource;
    void *key;
    ActorSlotHeader saved;

    slot->resource = data_ov036_020c3940.work->pendingResource;
    data_ov036_020c3940.work->pendingResource = NULL;
    data_02060570 = LoadTextureInChunks;
    key = AcquireOrRefreshResourceBlock(slot->resource, NULL, 1);
    func_0202c6a4(1);
    MI_CpuCopy8(slot, &saved, sizeof(ActorSlotHeader));
    SetSlotKeyAndRebind(slot, key, 0);
    slot->header.drawFlags = saved.drawFlags;
    slot->header.drawParam = saved.drawParam;
    if (saved.priority != 0) {
        slot->header.priority = saved.priority;
    }
    if (oldResource != NULL) {
        ReleaseResourceSlot(oldResource);
        ReleaseSharedRecordSlot(oldResource);
    } else if (slot->header.posY == 0) {
        slot->header.posY = func_ov036_020bb8ec(slot->header.height);
    }
}
