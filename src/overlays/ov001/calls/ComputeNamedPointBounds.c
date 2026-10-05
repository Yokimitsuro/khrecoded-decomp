#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 nameId;
    u8 pad_01[7];
} PointRecord;

typedef struct {
    u8 pad_00[0x20];
    PointRecord *records;
} PointSet;

typedef struct {
    u8 pad_00[8];
    PointSet *sets[1];
} PointTable;

typedef struct {
    u16 pad_00;
    u16 count;
    void **models;
} ModelGroup;

typedef struct {
    VecFx32 min;
    VecFx32 max;
} Bounds;

extern PointTable **data_ov001_020a048c;
extern char sOv001_FormatSFormat02d_0209ea90[];
extern char sOv001_Gate_0209ea98[];
extern ModelGroup *GetActorRegistry(void);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern int strlen(const char *str);
extern char *func_ov001_020670b4(void *owner, const char *name, int length, int *index);
extern void ForEachFaceOnPoint(void *model, u8 kindMask, char *point, void *callback, void *arg);
extern void ExpandBoundsByArea(void);
extern void MIi_CpuCopy32(const void *src, void *dst, u32 size);

BOOL ComputeNamedPointBounds(int setIndex, int recordIndex, VecFx32 *outMin, VecFx32 *outMax)
{
    int i;
    ModelGroup *group;
    char name[8];
    int index;
    Bounds bounds;

    group = GetActorRegistry();
    OS_SPrintf(name, sOv001_FormatSFormat02d_0209ea90, sOv001_Gate_0209ea98,
                        (*data_ov001_020a048c)->sets[setIndex]->records[recordIndex].nameId);
    bounds.min.z = 0x7fffffff;
    bounds.min.y = 0x7fffffff;
    bounds.min.x = 0x7fffffff;
    bounds.max.z = 0x80000000;
    bounds.max.y = 0x80000000;
    bounds.max.x = 0x80000000;
    for (i = 0; i < group->count; i++) {
        void *model = group->models[i];
        char *entry;
        index = 0;
        for (;;) {
            entry = func_ov001_020670b4(model, name, strlen(name), &index);
            if (entry == 0) {
                break;
            }
            ForEachFaceOnPoint(model, 2, entry, ExpandBoundsByArea, &bounds);
            index++;
        }
    }
    if (bounds.min.x != 0x7fffffff && bounds.max.x != 0x80000000) {
        MIi_CpuCopy32(&bounds.min, outMin, sizeof(VecFx32));
        MIi_CpuCopy32(&bounds.max, outMax, sizeof(VecFx32));
        return TRUE;
    }
    return FALSE;
}


