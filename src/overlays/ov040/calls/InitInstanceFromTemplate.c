#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TemplatePart {
    u8 pad_00[0x08];
    s32 offsetZ;
    u8 pad_0C[0x1D - 0x0C];
    u8 hasLift;
    u8 pad_1E[0x38 - 0x1E];
} TemplatePart;

typedef struct TemplateEntry {
    u8 id;
    u8 partCount;
    u16 unk_02;
    s32 unk_04;
    VecFx32 position;
    s8 unk_14[4];
    u8 unk_18;
    u8 unk_19;
    u8 pad_1A[2];
    s32 scaleX;
    s32 scaleZ;
    s32 scaleW;
    s32 unk_28;
    u16 unk_2C;
    u16 unk_2E;
    u8 unk_30;
    u8 unk_31;
    u8 unk_32;
    u8 unk_33;
    u8 unk_34;
    u8 unk_35;
    u8 unk_36;
    u8 unk_37;
    TemplatePart parts[4];
} TemplateEntry;

typedef struct TemplateTable {
    u16 count;
    u16 pad_02;
    TemplateEntry entries[1];
} TemplateTable;

typedef struct SizeParams {
    s32 sizeW;
    s32 sizeX;
    s32 sizeY;
    s32 sizeZ;
    u8 unk_10;
    u8 pad_11[3];
} SizeParams;

typedef struct SizeParamTable {
    u32 unk_00;
    SizeParams params[1];
} SizeParamTable;

typedef struct InstanceKey {
    u8 id;
    u8 paramIndex;
    s8 unk_02;
    s8 unk_03;
} InstanceKey;

typedef struct ObjectInstance {
    s32 sizeX;
    s32 sizeY;
    s32 sizeZ;
    s32 unk_0C;
    u32 sizeW;
    s32 unk_14;
    VecFx32 position;
    s32 unk_24;
    u16 unk_28;
    u16 unk_2A;
    u16 unk_2C;
    u8 pad_2E[2];
    u8 unk_30;
    u8 unk_31;
    u8 unk_32;
    u8 unk_33;
    u8 unk_34;
    u8 unk_35;
    u8 unk_36;
    u8 unk_37;
    u8 unk_38;
    u8 unk_39;
    s8 unk_3A[4];
    u8 id;
    s8 unk_3F;
    s8 unk_40;
    s8 partCount;
    u8 pad_42[2];
    TemplatePart *parts;
} ObjectInstance;

extern int FX_Mul(int left, int right);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);

void InitInstanceFromTemplate(TemplateTable *table, SizeParamTable *paramTable, InstanceKey *key, ObjectInstance *instance)
{
    TemplateEntry *entry;
    SizeParams *params;
    int index;
    int lift;

    entry = NULL;
    params = &paramTable->params[key->paramIndex];
    for (index = 0; index < table->count; index++) {
        if (key->id == table->entries[index].id) {
            entry = &table->entries[index];
            break;
        }
    }

    instance->sizeX = params->sizeX * entry->scaleX;
    instance->sizeY = params->sizeY << 12;
    instance->sizeZ = params->sizeZ * entry->scaleZ;
    instance->unk_0C = params->unk_10 << 12;
    instance->sizeW = (u32)(params->sizeW * entry->scaleW) >> 12;
    instance->unk_14 = entry->unk_04;
    instance->position = entry->position;
    instance->unk_24 = entry->unk_28;
    instance->unk_28 = entry->unk_2C;
    instance->unk_2A = entry->unk_2E;
    instance->unk_2C = entry->unk_02;
    instance->unk_30 = entry->unk_18;
    instance->unk_31 = entry->unk_19;
    instance->unk_32 = entry->unk_30;
    instance->unk_33 = entry->unk_31;
    instance->unk_34 = entry->unk_32;
    instance->unk_35 = entry->unk_33;
    instance->unk_36 = entry->unk_34;
    instance->unk_37 = entry->unk_35;
    instance->unk_38 = entry->unk_36;
    instance->unk_39 = entry->unk_37;
    for (index = 0; index < 4; index++) {
        instance->unk_3A[index] = entry->unk_14[index];
    }
    instance->id = key->id;
    instance->unk_3F = key->unk_02;
    instance->unk_40 = key->unk_03;
    instance->partCount = entry->partCount;
    instance->parts = NNSi_FndAllocFromDefaultHeap(instance->partCount * sizeof(TemplatePart));
    for (index = 0; index < instance->partCount; index++) {
        MIi_CpuCopyFast(&entry->parts[index], &instance->parts[index], sizeof(TemplatePart));
        if (instance->parts[index].hasLift) {
            lift = FX_Mul(0x40, instance->sizeY);
            lift = FX_Mul(lift, lift);
            lift = FX_Mul(lift + 0x10000, 0x100);
            instance->parts[index].offsetZ += lift - 0x1000;
        }
    }
}
