#include "nitro/types.h"

typedef struct EntryGroupDesc {
    u32 unk_00;
    u32 paletteParams;
    u32 mode;
    u32 vramParams;
    u32 fixedSlots;
} EntryGroupDesc;

typedef struct PaletteIdTable {
    u32 ids[7];
} PaletteIdTable;

typedef struct CueEntry {
    s16 id;
    u8 pad_02[10];
} CueEntry;

typedef struct CueList {
    CueEntry entries[21];
    u8 pad_fc[4];
    int count;
} CueList;

typedef struct SelectionRecord {
    u8 kind;
    u8 pad_01[0x2b];
    CueList cues;
} SelectionRecord;

typedef struct MotionRecord {
    u8 data[0x2c];
} MotionRecord;

typedef struct Entity {
    u8 pad_000[0x230];
    u8 *resourceHeader;
    u8 pad_234[0x76c - 0x234];
    MotionRecord motions[3];
    u8 pad_7f0[0x98c - 0x7f0];
    int (*mapCode)(int code);
    u8 pad_990[0x9b4 - 0x990];
    u8 selection;
    u8 pad_9b5[3];
    int nameIndex;
    u8 pad_9bc[0x1278 - 0x9bc];
    s16 rewardGroupIds[7];
} Entity;

extern const char *gSoundCategoryNames[];
extern char sOv054_BaChFormatSEtc2PZ_020d36c0[];
extern char sOv054_BaChFormatSAb2PZ_020d36d4[];
extern char sOv054_BaChFormatSJpPZ_020d36e8[];
extern char data_ov054_020d36f8[];
extern PaletteIdTable data_ov054_020d3674;
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void AcquireSharedRecordState(void *state, char *name, void *data, int context);
extern BOOL IsPlayerEntryFlagSet(u32 selection, int flag);
extern u32 func_ov001_0206dba0(int index);
extern SelectionRecord *GetOverlaySelectionRecord(u32 index);
extern void ZeroBytes0x14(EntryGroupDesc *desc);
extern s16 func_ov021_020a89c8(EntryGroupDesc *desc);
extern int MapCodeToSlotIndex(int code);

void LoadOverlay054EntityResources(Entity *entity)
{
    char name[0x80];
    PaletteIdTable table;
    EntryGroupDesc group;
    int context = entity->selection + 8;
    MotionRecord *record;
    u32 vramBase;
    u32 mask;
    int i;
    SelectionRecord *selection;
    CueList *cues;
    u32 params;

    OS_SPrintf(name, sOv054_BaChFormatSEtc2PZ_020d36c0, gSoundCategoryNames[entity->nameIndex]);
    AcquireSharedRecordState(&entity->motions[0], name, entity->resourceHeader + 4, context);
    OS_SPrintf(name, sOv054_BaChFormatSAb2PZ_020d36d4, gSoundCategoryNames[entity->nameIndex]);
    AcquireSharedRecordState(&entity->motions[2], name, entity->resourceHeader + 4, context);
    record = &entity->motions[1];
    if (!IsPlayerEntryFlagSet(entity->selection, 0xc)) {
        OS_SPrintf(name, sOv054_BaChFormatSJpPZ_020d36e8, gSoundCategoryNames[entity->nameIndex]);
    } else {
        OS_SPrintf(name, data_ov054_020d36f8, gSoundCategoryNames[entity->nameIndex]);
    }
    AcquireSharedRecordState(record, name, entity->resourceHeader + 4, context);
    vramBase = func_ov001_0206dba0(3);
    table = data_ov054_020d3674;
    mask = 0;
    selection = GetOverlaySelectionRecord(entity->selection);
    cues = &selection->cues;
    for (i = 0; i < cues->count; i++) {
        switch (cues->entries[i].id) {
        case 0xb7:
            mask |= 1;
            break;
        case 0xb8:
            mask |= 2;
            break;
        case 0xb9:
            mask |= 4;
            break;
        case 0xba:
            mask |= 8;
            break;
        case 0xbb:
            mask |= 0x10;
            break;
        case 0xbc:
            mask |= 0x20;
            break;
        case 0xbd:
            mask |= 0x40;
            break;
        }
    }
    params = 0x80000000 | (((vramBase + 0x8000) & 0xfffffc) << 7);
    for (i = 0; i < 7; i++) {
        entity->rewardGroupIds[i] = -1;
        if (mask & (1 << i)) {
            ZeroBytes0x14(&group);
            group.vramParams = (table.ids[i] & 0x1ff) | params;
            group.paletteParams = ((table.ids[i] + 1) & 0x1ff) | params;
            group.mode = 3;
            group.fixedSlots = 1;
            entity->rewardGroupIds[i] = func_ov021_020a89c8(&group);
        }
    }
    entity->mapCode = MapCodeToSlotIndex;
}
