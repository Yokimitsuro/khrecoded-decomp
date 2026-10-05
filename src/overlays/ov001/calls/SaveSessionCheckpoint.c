#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SaveSnapshot {
    u8 core[0xc49];
    s8 unk_C49;
    u8 rest[0x1cb4 - 0xc4a];
} SaveSnapshot;

typedef struct Checkpoint {
    VecFx32 positions[3];
    u16 angles[3];
    s16 area;
    s16 sessionValue;
    u8 pad_2e[2];
    u32 playTime;
    u8 pad_34[4];
    SaveSnapshot snapshot;
    SaveSnapshot *saved;
} Checkpoint;

typedef struct Session {
    u8 pad_0000[0x20a];
    s16 area;
    u8 pad_020c[0x214 - 0x20c];
    u32 unk_214_0 : 3;
    u32 locked : 1;
    u8 pad_0218[0x220 - 0x218];
    Checkpoint checkpoint;
    u8 pad_1f10[0x2748 - 0x1f10];
    VecFx32 positions[3];
    u16 angles[3];
    u8 pad_2772[0x2938 - 0x2772];
    u32 playTime;
} Session;

typedef struct SaveSection {
    u8 pad_00[0x4d];
    s8 unk_4D;
} SaveSection;

typedef struct SaveBits {
    u8 pad_0000[0x2888];
    SaveSection section;
} SaveBits;

extern Session *data_ov001_020a0480;
extern SaveBits *data_0205fe0c;

extern int func_ov001_020644b0(void);
extern s32 func_ov001_02063a38(void);
extern BOOL func_ov001_020645c8(u32 value);
extern void StoreSessionDifficultyPreset(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void CaptureSaveSnapshot(SaveSnapshot *snapshot);
extern int func_ov001_02068378(void);
extern int func_ov001_02067ed4(void);

void SaveSessionCheckpoint(u32 flags)
{
    Session *session = data_ov001_020a0480;
    Checkpoint *checkpoint = &session->checkpoint;
    u32 forced = flags & 0x80;
    int i;

    if (forced && session->locked) {
        return;
    }
    if (!forced) {
        if (func_ov001_020644b0() == 400) {
            return;
        }
        if (func_ov001_02063a38() == 10) {
            return;
        }
        if (func_ov001_020645c8(0x3626)) {
            return;
        }
    }
    if (flags & 2) {
        StoreSessionDifficultyPreset();
        if (flags & 0x40) {
            if (checkpoint->saved != NULL) {
                NNSi_FndFreeFromDefaultHeap(checkpoint->saved);
            }
            checkpoint->saved = NNS_FndAllocFromDefaultExpHeapEx(sizeof(SaveSnapshot), -4);
            CaptureSaveSnapshot(checkpoint->saved);
        } else if (!forced && checkpoint->saved != NULL) {
            MI_CpuCopy8(checkpoint->saved, &checkpoint->snapshot, sizeof(SaveSnapshot));
            NNSi_FndFreeFromDefaultHeap(checkpoint->saved);
            checkpoint->saved = NULL;
        } else {
            CaptureSaveSnapshot(&checkpoint->snapshot);
        }
        checkpoint->playTime = session->playTime;
    }
    if (flags & 1) {
        for (i = 0; i < 3; i++) {
            checkpoint->positions[i] = session->positions[i];
            checkpoint->angles[i] = session->angles[i];
        }
        checkpoint->area = session->area;
        if (func_ov001_02068378()) {
            checkpoint->sessionValue = func_ov001_02067ed4();
            checkpoint->snapshot.unk_C49 = data_0205fe0c->section.unk_4D;
        } else {
            checkpoint->sessionValue = -1;
        }
    }
}
