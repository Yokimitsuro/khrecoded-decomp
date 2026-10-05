#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x18];
    void *objectHeap;
    u8 pad_1c[0x18];
    void *heap;
    void *savedHeap;
} HeapScope;

typedef struct {
    u8 pad_00[0x18e14];
    HeapScope heapScope;
} StageManager;

typedef struct ModelHeader {
    u16 unk_00;
    u16 version;
} ModelHeader;

typedef struct ModelDef {
    ModelHeader *header;
    u8 pad_04[0x7c];
    u32 resource;
    u8 pad_84[0x6c];
    void *textureInfo;
} ModelDef;

typedef struct StageObject {
    u8 pad_000[0x14];
    u8 textureDest[0xd8];
    u8 textureSrc[0xd8];
    u16 unk_1c4;
} StageObject;

extern StageManager *data_ov001_020a0528;
extern const VecFx32 data_0205344c;
extern void *Heap_GetCurrent(void);
extern void *SetDefaultHeap(void *heap);
extern BOOL ActivateEntrySubobject(StageObject *object, u32 resource, u32 param3, u32 param4);
extern BOOL PrepareTextureAndDispatch(void *dst, void *src, void *info);
extern void ActorSlot_PlaceAndLink(StageObject *object, int anchor, const VecFx32 *offset);

void InitStageObjectModel(StageObject *object, ModelDef *def)
{
    StageManager *manager = data_ov001_020a0528;

    if (manager == NULL || def == NULL) {
        return;
    }
    if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap == NULL) {
        manager->heapScope.savedHeap = Heap_GetCurrent();
        SetDefaultHeap(manager->heapScope.objectHeap);
    }
    object->unk_1c4 = 0;
    ActivateEntrySubobject(object, def->resource, 0, 0xb);
    if (def->header->version > 3) {
        PrepareTextureAndDispatch(object->textureSrc, object->textureDest, def->textureInfo);
    }
    ActorSlot_PlaceAndLink(object, 0, &data_0205344c);
    manager = data_ov001_020a0528;
    if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap != NULL) {
        SetDefaultHeap(manager->heapScope.savedHeap);
        manager->heapScope.savedHeap = NULL;
    }
}
