#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*UnitCallback)(void);

typedef struct UnitDesc {
    u8 slotCount;
    s8 cellCount;
    u8 pad_02[0x2];
    int linkCount;
} UnitDesc;

typedef struct UnitRecord {
    u8 pad_00[0x10];
    u8 active : 1;
    u8 rest : 7;
    u8 pad_11[0xc4 - 0x11];
} UnitRecord;

typedef struct UnitObject {
    u8 pad_00[0x4];
    struct FieldUnit *owner;
    u8 pad_08[0x33 - 0x8];
    u8 index;
    u8 pad_34[0x70 - 0x34];
    u16 drawFlags;
} UnitObject;

typedef struct FieldUnit {
    UnitCallback callbacks[15];
    u16 stride;
    u16 count;
    u8 *entries;
    fx32 radius;
    fx32 height;
    fx32 scale[3];
    u8 layer;
    u8 pad_59;
    u8 category;
    u8 pad_5b[0x5];
    void *slots[21];
    s16 activeIndex;
    u8 pad_b6[0x2];
    void *cells;
    void *links;
    u16 cellCount;
    u16 linkCount;
    UnitRecord *records;
    u16 slotCount : 5;
    u16 slotFlags : 11;
    u16 slotCursor;
    void *slotData;
    void *workBuffer;
} FieldUnit;

extern FieldUnit *CreateEntryPool(int headerSize, int entrySize, int count);
extern UnitObject *func_ov001_02086384(FieldUnit *unit, int index);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int alignment);
extern void func_01ff88c4(void *dst, u32 value, u32 size);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void ApplyFieldObjectSpawnEntry(UnitObject *object);
extern void LoadFieldUnitModel(void);
extern void RefreshFieldObjectPhase(void);
extern void FreeHeapRecord(void);
extern void ReleaseFieldSceneResources(void);
extern void func_ov016_020a5d38(void);
extern void SetFieldObjectVisible(void);
extern void HandleFieldObjectHit_020a50a4(void);
extern void GetFieldUnitVelocity(void);
extern void DispatchCollisionUnlessSameSlot(void);
extern void GetFieldUnitTopPosition(void);
extern void func_ov016_020a5b40(void);
extern void GetFieldUnitPosition(void);
extern void HasFieldUnitPhase(void);
extern void DrawFieldUnitObject(void);

FieldUnit *CreateFieldUnit(int count, UnitDesc *desc, UnitRecord *records)
{
    FieldUnit *unit = CreateEntryPool(sizeof(FieldUnit), 0xf8, count);
    int i;
    int index;
    u32 size;
    u8 slotCount;

    unit->height = 0;
    unit->layer = 3;
    unit->scale[0] = 0x1800;
    unit->scale[1] = 0x1800;
    unit->scale[2] = 0x1800;
    unit->radius = 0x3000;
    unit->callbacks[0] = LoadFieldUnitModel;
    unit->callbacks[1] = RefreshFieldObjectPhase;
    unit->callbacks[2] = NULL;
    unit->callbacks[4] = FreeHeapRecord;
    unit->callbacks[5] = ReleaseFieldSceneResources;
    unit->callbacks[13] = func_ov016_020a5d38;
    unit->callbacks[6] = SetFieldObjectVisible;
    unit->callbacks[7] = HandleFieldObjectHit_020a50a4;
    unit->callbacks[8] = GetFieldUnitVelocity;
    unit->callbacks[9] = DispatchCollisionUnlessSameSlot;
    unit->callbacks[10] = GetFieldUnitTopPosition;
    unit->callbacks[3] = func_ov016_020a5b40;
    unit->callbacks[11] = GetFieldUnitPosition;
    unit->callbacks[12] = HasFieldUnitPhase;
    unit->callbacks[14] = DrawFieldUnitObject;
    unit->category = 9;
    unit->records = records;
    for (i = 0; i < 21; i++) {
        unit->slots[i] = NULL;
    }
    unit->activeIndex = -1;
    if (records != NULL) {
        for (index = 0; index < count; index++) {
            UnitObject *object = func_ov001_02086384(unit, index);

            object->owner = unit;
            object->index = index;
            if (records[index].active) {
                object->drawFlags |= 0x40;
                ApplyFieldObjectSpawnEntry(object);
            }
        }
    }
    if (desc != NULL) {
        u32 cellSize = desc->cellCount;

        size = desc->linkCount * 0x14;
        unit->cellCount = cellSize;
        cellSize *= 4;
        unit->cells = NNS_FndAllocFromDefaultExpHeapEx(cellSize, 4);
        func_01ff88c4(unit->cells, 0, cellSize);
        if (size != 0) {
            unit->linkCount = desc->linkCount;
            unit->links = NNS_FndAllocFromDefaultExpHeapEx(size, 4);
            func_01ff88c4(unit->links, 0, size);
        }
        slotCount = desc->slotCount;
        if (slotCount != 0) {
            unit->slotCount = slotCount;
            size = slotCount * 0x1e0;
            unit->slotData = NNS_FndAllocFromDefaultExpHeapEx(size, 4);
            func_01ff88c4(unit->slotData, 0, size);
            unit->slotCursor = 0;
            if (unit->records != NULL) {
                MIi_CpuCopyFast(&unit->records[unit->count], unit->slotData, unit->slotCount * 0x1e0);
            }
            unit->workBuffer = NNS_FndAllocFromDefaultExpHeapEx(0x168, 4);
        } else {
            unit->slotData = NULL;
            unit->workBuffer = NULL;
        }
    }
    return unit;
}
