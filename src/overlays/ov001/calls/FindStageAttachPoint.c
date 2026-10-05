#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AttachPoint {
    u32 key;
    s32 nameIndex;
    u8 pad_08[0xc];
    VecFx32 scale;
} AttachPoint;

typedef struct AttachTable {
    u8 pad_00[0x34];
    u32 count;
    u32 stride;
    u8 *items;
} AttachTable;

typedef struct StageResource {
    u8 pad_00[8];
    AttachTable *table;
} StageResource;

typedef struct StageEntry {
    u8 pad_00[4];
    StageResource *resource;
} StageEntry;

typedef struct StageObject {
    u8 pad_00[0x14];
    s16 entryId;
} StageObject;

extern u8 data_ov001_020a0314[];
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern StageEntry *GetStageEntry(int id);
extern s32 func_ov001_0208f040(StageResource *resource, int index);

static inline u32 GetAttachCount(StageEntry *entry)
{
    u32 count = 0;

    if (entry != NULL && entry->resource != NULL) {
        count = entry->resource->table->count;
    }
    return count;
}

static inline u32 GetAttachCountChecked(StageEntry *entry)
{
    if (entry == NULL) {
        return 0;
    }
    if (entry->resource == NULL) {
        return 0;
    }
    return entry->resource->table->count;
}

static inline AttachPoint *GetAttachPoint(StageEntry *entry, u32 index)
{
    StageResource *resource;
    u32 count;
    u8 *items;

    if (entry == NULL) {
        return NULL;
    }
    resource = entry->resource;
    if (resource == NULL) {
        return NULL;
    }
    count = GetAttachCountChecked(entry);
    items = resource->table->items;
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return (AttachPoint *)(items + index * resource->table->stride);
}

void FindStageAttachPoint(StageObject *object, u32 key, AttachPoint *out)
{
    StageEntry *entry;
    AttachPoint *point;
    u16 count;
    u16 i;

    MI_CpuFill8(out, 0, sizeof(AttachPoint));
    out->scale.x = 0x1000;
    out->scale.y = 0x1000;
    out->scale.z = 0x1000;
    out->nameIndex = (s32)data_ov001_020a0314;
    entry = GetStageEntry(object->entryId);
    if (entry == NULL) {
        return;
    }
    count = GetAttachCount(entry);
    if (count == 0) {
        return;
    }
    for (i = 0; i < count; i++) {
        point = GetAttachPoint(entry, i);
        if (point->key == key) {
            *out = *point;
            out->nameIndex = func_ov001_0208f040(entry->resource, out->nameIndex);
            return;
        }
    }
}
