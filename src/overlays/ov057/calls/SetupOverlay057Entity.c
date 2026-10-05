#include "nitro/types.h"

typedef struct CueEntry {
    s16 id;
    u8 pad_02[2];
    u8 variant;
    u8 pad_05[7];
} CueEntry;

typedef struct CueList {
    CueEntry entries[21];
    u8 pad_fc[4];
    int count;
    CueEntry extra;
} CueList;

typedef struct SelectionRecord {
    u8 kind;
    u8 pad_01[0x2b];
    CueList cues;
} SelectionRecord;

typedef struct CueSetup {
    u32 selection;
    void *unit;
    void *resources;
    void *model;
} CueSetup;

typedef struct ResourceOwner {
    u8 pad_00[4];
    u8 data[4];
} ResourceOwner;

typedef struct FieldInfo {
    u16 pad_00;
    u16 value;
    u16 extra;
} FieldInfo;

typedef struct Entity Entity;
struct Entity {
    u8 pad_000[0x1d4];
    FieldInfo *field;
    u8 pad_1d8[0x1f8 - 0x1d8];
    void (*onEvent)(Entity *entity, int event, int value);
    u8 pad_1fc[0x230 - 0x1fc];
    ResourceOwner *owner;
    u8 pad_234[0x76c - 0x234];
    u8 firstRecord[0x798 - 0x76c];
    u8 thirdRecord[0x848 - 0x798];
    u8 secondRecord[0x98c - 0x848];
    int (*mapCode)(int code);
    u8 pad_990[0x9b4 - 0x990];
    u8 kind;
    u8 pad_9b5[3];
    int nameIndex;
    u8 pad_9bc[0xb68 - 0x9bc];
    u8 model[0xfc8 - 0xb68];
    u8 unit[0x1070 - 0xfc8];
    u8 cuePlayer[4];
};

extern const char *gSoundCategoryNames[];
extern const char sOv057_BaChFormatSDefPZ_020d44c0[];
extern const char sOv057_BaChFormatSEtcPZ_020d44d4[];
extern const char sOv057_BaChFormatSJpPZ_020d44e8[];

extern void *OS_SPrintf(char *dst, const char *fmt, ...);
extern void AcquireSharedRecordState(void *obj, char *key, void *initArg, u32 context);
extern void LoadOverlay057EntityModel(Entity *entity);
extern SelectionRecord *GetOverlaySelectionRecord(unsigned int selectionIndex);
extern int ResolveEventVariant(int eventId);
extern void LoadSelectionCues(void *player, CueSetup *setup);
extern int MapSceneIdToSlot(int code);
extern void SetFieldSlotValue(int index, int value, int param, int extra);

void SetupOverlay057Entity(Entity *entity)
{
    u32 context = entity->kind + 8;
    CueList *base;
    CueList *cues;
    CueSetup setup;
    char name[0x80];
    int i;

    OS_SPrintf(name, sOv057_BaChFormatSDefPZ_020d44c0, gSoundCategoryNames[entity->nameIndex]);
    AcquireSharedRecordState(entity->firstRecord, name, entity->owner->data, context);
    OS_SPrintf(name, sOv057_BaChFormatSEtcPZ_020d44d4, gSoundCategoryNames[entity->nameIndex]);
    AcquireSharedRecordState(entity->secondRecord, name, entity->owner->data, context);
    OS_SPrintf(name, sOv057_BaChFormatSJpPZ_020d44e8, gSoundCategoryNames[entity->nameIndex]);
    AcquireSharedRecordState(entity->thirdRecord, name, entity->owner->data, context);
    LoadOverlay057EntityModel(entity);

    i = 0;
    base = &GetOverlaySelectionRecord(0)->cues;
    cues = &GetOverlaySelectionRecord(entity->kind)->cues;
    cues->count = base->count;
    cues->extra.id = -1;
    for (; i < base->count; i++) {
        int id = ResolveEventVariant(i);
        if (id == 0xf5 || id == 0xf7) {
            cues->entries[i].id = id;
            cues->entries[i].variant = base->entries[i].variant;
        } else {
            cues->entries[i].id = -1;
        }
    }

    setup.selection = entity->kind;
    setup.unit = entity->unit;
    setup.resources = entity->owner->data;
    setup.model = entity->model;
    LoadSelectionCues(entity->cuePlayer, &setup);
    entity->mapCode = MapSceneIdToSlot;
    if (entity->kind != 0) {
        SetFieldSlotValue(entity->kind - 1, 3, entity->field->value, entity->field->extra);
    }
    if (entity->field->value == 0 && entity->onEvent != NULL) {
        entity->onEvent(entity, 10, -1);
    }
}
