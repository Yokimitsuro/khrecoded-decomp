#include "nitro/types.h"

typedef struct SlotEntry {
    u8 data[0x2c];
} SlotEntry;

typedef struct SlotArrays {
    SlotEntry *entries;
    int count;
    s8 *ids;
} SlotArrays;

typedef struct SlotModelObject {
    u8 pad00[0x78];
    void *model;
    u8 pad7c[0x104 - 0x7c];
    SlotArrays slots;
    u32 param;
} SlotModelObject;

typedef struct SlotIdList {
    int pad00;
    int count;
    s8 *ids;
} SlotIdList;

typedef struct SlotModelDesc {
    int group;
    int variant;
    SlotIdList *idList;
    u8 pad0c[8];
    u32 param;
} SlotModelDesc;

extern u32 MakePaletteUploadParams40(int group, int variant);
extern u32 MakePaletteUploadParams60(int group, int variant);
extern void *SND_RegisterSeq(u32 fileId, int heap);
extern void *func_0202c4a0(u32 fileId, u32 heapId);
extern void func_0202edb0(void *object, void *record, void *block, int heap);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void NNS_G3dMdlSetMdlPolygonIDAll(void *model, int polygonId);
extern void func_0202f5a4(void *object, int value);
extern void Obj_SetHalfwordFC(void *object, int color);
extern void AllocateObjectSlotArrays(SlotArrays *slots, int count, int heap);
extern char *GetTimedEntryKey(int id, int variant);
extern void AcquireSharedRecordState(void *state, char *key, void *object, int heap);

void LoadSlotModelObject(SlotModelObject *object, SlotModelDesc *desc, u8 bank)
{
    int heap;
    void *record;
    void *block;
    SlotIdList *idList;
    int i;
    int slot;
    int id;
    char *key;
    SlotArrays *slots;

    heap = bank + 8;
    object->param = desc->param;
    record = SND_RegisterSeq(MakePaletteUploadParams40(desc->group, desc->variant), heap);
    block = func_0202c4a0(MakePaletteUploadParams60(desc->group, desc->variant), 0x11);
    func_0202edb0(object, record, block, heap);
    NNSi_FndFreeFromDefaultHeap(block);
    NNS_G3dMdlSetMdlPolygonIDAll(object->model, 0x3f);
    func_0202f5a4(object, 1);
    Obj_SetHalfwordFC(object, 0x7fff);
    idList = desc->idList;
    i = 0;
    slots = &object->slots;
    slots->entries = NULL;
    slots->ids = NULL;
    slots->count = 0;
    AllocateObjectSlotArrays(slots, idList->count, heap);
    slot = 0;
    for (; i < idList->count; i++) {
        id = idList->ids[i];
        key = GetTimedEntryKey(id, desc->variant);
        if (key != NULL) {
            AcquireSharedRecordState(&slots->entries[slot], key, object, heap);
            slots->ids[slot] = id;
            slot++;
        }
    }
}
