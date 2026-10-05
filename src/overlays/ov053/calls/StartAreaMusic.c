#include "nitro/types.h"

typedef struct MusicInfo {
    u8 pad_00[0xc];
    s16 offset;
} MusicInfo;

typedef struct AreaInfo {
    u8 pad_000[0x104];
    s16 id;
} AreaInfo;

typedef struct SelectionRecord {
    u8 pad_000[0x10];
    MusicInfo music;
    u8 pad_01e[0x2c - 0x1e];
    AreaInfo area;
} SelectionRecord;

typedef struct Entity {
    u8 pad_000[0x9b4];
    u8 selection;
    u8 pad_9b5[0xb2c - 0x9b5];
    u8 musicPair[0x1070 - 0xb2c];
    u8 soundGroup[4];
} Entity;

extern u8 data_020608c8;
extern SelectionRecord *GetOverlaySelectionRecord(u32 index);
extern int func_ov001_02063a38(void);
extern BOOL func_ov001_0206e31c(void);
extern void SetSoundPairAndQueue(void *pair, int first, int second);
extern void SetSoundIdAndQueue(void *owner, int soundId);
extern void QueueSoundCommandForArc(int soundId);
extern void QueueGroupSounds(void *group);

void StartAreaMusic(Entity *entity)
{
    int first;
    int second;
    int soundId;
    MusicInfo *music;

    music = &GetOverlaySelectionRecord(entity->selection)->music;
    first = 0x30;
    second = music->offset + 0x48;
    if (data_020608c8 > 1) {
        first = 0x3e;
        second = -1;
    }
    SetSoundPairAndQueue(entity->musicPair, first, second);
    if (func_ov001_02063a38() != 6) {
        AreaInfo *area = &GetOverlaySelectionRecord(entity->selection)->area;
        soundId = -1;
        switch (area->id) {
        case 0xbe:
            soundId = 0x34;
            break;
        case 0xbf:
            soundId = 0x35;
            break;
        case 0xc0:
            soundId = 0x36;
            break;
        case 0xc1:
            soundId = 0x38;
            break;
        case 0xc2:
            soundId = 0x37;
            break;
        case 0xc3:
            soundId = 0x39;
            break;
        case 0xc4:
            soundId = 0x38;
            break;
        case 0xc5:
            soundId = 0x35;
            break;
        case 0xc6:
            soundId = 0x39;
            break;
        case 0xc7:
        case 0x10f:
            soundId = 0x3b;
            break;
        case 0xc8:
        case 0x110:
            soundId = 0x3c;
            break;
        case 0xc9:
        case 0x111:
            soundId = 0x3d;
            break;
        }
        SetSoundIdAndQueue(entity->musicPair, soundId);
        if (func_ov001_0206e31c() && soundId != 0x35) {
            QueueSoundCommandForArc(0x35);
        }
    }
    QueueGroupSounds(entity->soundGroup);
}
