#include "nitro/types.h"

typedef struct CueSource {
    u32 selection;
    void *unitResources;
    void *resourceData;
    void *modelObject;
} CueSource;

typedef struct EntryGroupDesc {
    char *name;
    u32 slotCount;
    u32 fixedSlots;
    u32 unk_0c;
    u32 unk_10;
} EntryGroupDesc;

typedef struct MotionRecord {
    u8 data[0x2c];
} MotionRecord;

typedef struct Entity {
    u8 pad_000[0x230];
    u8 *resourceHeader;
    u8 pad_234[0x76c - 0x234];
    MotionRecord motions[6];
    u8 pad_874[0x98c - 0x874];
    int (*mapKind)(int kind);
    u8 pad_990[0x9b4 - 0x990];
    u8 selection;
    u8 pad_9b5[3];
    int nameIndex;
    u8 pad_9bc[0xb68 - 0x9bc];
    u8 modelObject[0xfc8 - 0xb68];
    u8 unitResources[0x1070 - 0xfc8];
    u8 cues[0x1258 - 0x1070];
    u16 effectGroupId;
} Entity;

extern const char *gSoundCategoryNames[];
extern char sOv053_BaChFormatSDefPZ_020d2b80[];
extern char sOv053_BaChFormatSAbPZ_020d2b94[];
extern char sOv053_BaChFormatSJpPZ_020d2ba4[];
extern char sOv053_BaChFormatSHjpPZ_020d2bb4[];
extern char sOv053_BaChFormatSRefPZ_020d2bc8[];
extern char sOv053_BaChFormatSLaPZ_020d2bdc[];
extern char sOv053_BaChFormatSSpePZ_020d2bec[];
extern char sOv053_BaChFormatSEtcPZ_020d2c00[];
extern char sOv053_BaChFormatSEtc2PZ_020d2c14[];
extern char sOv053_BaChSoWd00_020d2c28[];
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void AcquireSharedRecordState(void *state, char *name, void *data, int context);
extern BOOL IsPlayerEntryFlagSet(u32 selection, int flag);
extern BOOL func_ov001_0206e2b0(void);
extern BOOL func_ov001_0206e31c(void);
extern BOOL func_ov001_020645c8(u32 value);
extern int func_ov001_02063a38(void);
extern void ZeroBytes0x14(EntryGroupDesc *desc);
extern u16 func_ov021_020a89c8(EntryGroupDesc *desc);
extern void func_ov053_020d23f8(Entity *entity);
extern void LoadOverlay053EntityModel(Entity *entity);
extern void LoadSelectionCues(void *cues, CueSource *source);
extern void func_ov040_020bdf9c(Entity *entity, CueSource *source);
extern void func_ov010_020a17c0(Entity *entity);
extern int MapKindToSlotIndex(int kind);

void LoadOverlay053EntityResources(Entity *entity)
{
    EntryGroupDesc group;
    CueSource source;
    char name[0x80];
    int context = entity->selection + 8;
    MotionRecord *record;

    OS_SPrintf(name, sOv053_BaChFormatSDefPZ_020d2b80, gSoundCategoryNames[entity->nameIndex]);
    AcquireSharedRecordState(&entity->motions[0], name, entity->resourceHeader + 4, context);
    OS_SPrintf(name, sOv053_BaChFormatSAbPZ_020d2b94, gSoundCategoryNames[entity->nameIndex]);
    AcquireSharedRecordState(&entity->motions[2], name, entity->resourceHeader + 4, context);
    record = &entity->motions[1];
    if (!IsPlayerEntryFlagSet(entity->selection, 0xc) || func_ov001_0206e2b0()) {
        OS_SPrintf(name, sOv053_BaChFormatSJpPZ_020d2ba4, gSoundCategoryNames[entity->nameIndex]);
    } else {
        OS_SPrintf(name, sOv053_BaChFormatSHjpPZ_020d2bb4, gSoundCategoryNames[entity->nameIndex]);
    }
    AcquireSharedRecordState(record, name, entity->resourceHeader + 4, context);
    OS_SPrintf(name, sOv053_BaChFormatSRefPZ_020d2bc8, gSoundCategoryNames[entity->nameIndex]);
    AcquireSharedRecordState(&entity->motions[3], name, entity->resourceHeader + 4, context);
    record = &entity->motions[4];
    if (!func_ov001_0206e31c()) {
        OS_SPrintf(name, sOv053_BaChFormatSLaPZ_020d2bdc, gSoundCategoryNames[entity->nameIndex]);
    } else {
        OS_SPrintf(name, sOv053_BaChFormatSSpePZ_020d2bec, gSoundCategoryNames[entity->nameIndex]);
    }
    AcquireSharedRecordState(record, name, entity->resourceHeader + 4, context);
    if (!func_ov001_020645c8(0x3609) && !func_ov001_020645c8(0x360a) && !func_ov001_020645c8(0x360b)) {
        OS_SPrintf(name, sOv053_BaChFormatSEtcPZ_020d2c00, gSoundCategoryNames[entity->nameIndex]);
    } else {
        OS_SPrintf(name, sOv053_BaChFormatSEtc2PZ_020d2c14, gSoundCategoryNames[entity->nameIndex]);
    }
    AcquireSharedRecordState(&entity->motions[5], name, entity->resourceHeader + 4, context);
    ZeroBytes0x14(&group);
    OS_SPrintf(name, sOv053_BaChSoWd00_020d2c28);
    group.name = name;
    group.slotCount = 1;
    group.fixedSlots = 1;
    group.unk_0c = 0;
    entity->effectGroupId = func_ov021_020a89c8(&group);
    func_ov053_020d23f8(entity);
    LoadOverlay053EntityModel(entity);
    source.selection = entity->selection;
    source.unitResources = entity->unitResources;
    source.resourceData = entity->resourceHeader + 4;
    source.modelObject = entity->modelObject;
    LoadSelectionCues(entity->cues, &source);
    if (func_ov001_02063a38() == 6) {
        func_ov040_020bdf9c(entity, &source);
    }
    entity->mapKind = MapKindToSlotIndex;
    if (func_ov001_0206e31c()) {
        func_ov010_020a17c0(entity);
    }
}
