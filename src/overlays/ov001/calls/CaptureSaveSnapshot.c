#include "nitro/types.h"

typedef struct NibblePair {
    u8 low : 4;
    u8 high : 4;
} NibblePair;

typedef struct SaveSection {
    u8 header[0x3c];
    u32 unk_3C;
    u32 unk_40;
    u32 unk_44;
    u32 unk_48;
    s8 unk_4C;
    u8 unk_4D;
    u8 unk_4E;
    NibblePair nibbles;
    u8 body[0xe88];
} SaveSection;

typedef struct SaveBits {
    u8 core[0xc00];
    u8 pad_0c00[0x2888 - 0xc00];
    SaveSection section;
} SaveBits;

typedef struct SaveSnapshot {
    u8 core[0xc00];
    u8 header[0x3c];
    u32 unk_C3C;
    u32 unk_C40;
    u32 unk_C44;
    s8 unk_C48;
    u8 pad_C49;
    u8 unk_C4A;
    NibblePair nibbles;
    u8 body[0xe88];
    u8 difficultyPreset[0x1e0];
} SaveSnapshot;

typedef struct Session {
    u8 pad_0000[0x28];
    u8 difficultyPreset[0x1e0];
} Session;

extern SaveBits *data_0205fe0c;
extern Session *data_ov001_020a0480;
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);
extern u32 ReadGlobalPackedBits(u32 bitOffset, u32 bitCount);

void CaptureSaveSnapshot(SaveSnapshot *snapshot) {
    MIi_CpuCopyFast(data_0205fe0c->core, snapshot->core, 0xc00);
    MIi_CpuCopy16(data_0205fe0c->section.header, snapshot->header, 0x3c);
    snapshot->unk_C3C = data_0205fe0c->section.unk_3C;
    snapshot->unk_C40 = data_0205fe0c->section.unk_44;
    snapshot->unk_C44 = data_0205fe0c->section.unk_48;
    snapshot->unk_C48 = data_0205fe0c->section.unk_4C;
    snapshot->unk_C4A = data_0205fe0c->section.unk_4E;
    snapshot->nibbles.low = data_0205fe0c->section.nibbles.low;
    snapshot->nibbles.high = data_0205fe0c->section.nibbles.high;
    MIi_CpuCopyFast(data_0205fe0c->section.body, snapshot->body, 0xe88);
    if (ReadGlobalPackedBits(0x1a00, 2) == 3) {
        MIi_CpuCopyFast(data_ov001_020a0480->difficultyPreset, snapshot->difficultyPreset, 0x1e0);
    }
}
