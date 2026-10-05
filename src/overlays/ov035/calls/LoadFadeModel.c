#include "nitro/types.h"

typedef struct FadeEntry {
    s8 material;
    s8 target;
    s8 value;
    u8 unknown_03;
} FadeEntry;

typedef struct MaterialDict {
    u8 unknown_00[2];
    u16 namesOffset;
} MaterialDict;

typedef struct MaterialSet {
    u8 unknown_00[5];
    u8 count;
    u8 unknown_06[4];
    u16 dictOffset;
} MaterialSet;

typedef struct ModelResource {
    u8 unknown_00[8];
    u32 materialsOffset;
} ModelResource;

typedef struct FadeWork {
    u8 unknown_000[0x78];
    ModelResource *model;
    u8 unknown_07c[0x5c];
    s16 animCounts[5];
    u8 unknown_0e2[0x22];
    s16 modelIdA;
    s16 modelIdB;
    u8 unknown_108;
    s8 current;
    s8 count;
    u8 active;
    FadeEntry *entries;
} FadeWork;

extern FadeWork *data_ov035_020bc504;
extern const char data_ov035_020bc4c8[];
extern const char data_ov035_020bc4d0[];
extern u32 ObjectManager_GetSecondEntryParam(int index);
extern u32 ObjectManager_GetFirstEntryParam(int index);
extern void *func_0202c4a0(u32 fileId, u32 alignFlag);
extern void InitSharedRecordAndDispatchAlt(void *dst, int a, void *info, int b);
extern void selectJointAnimationBlend(FadeWork *work, u16 trackIndex, s16 *blendTable, s16 blendIndex);
extern int *func_01ffb2f8(FadeWork *work, int trackIndex, int arg);
extern void Flags16_ClearBit1(FadeWork *work);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void *OS_SPrintf(char *dst, const char *fmt, ...);
extern int strcmp(const char *str1, const char *str2);
extern void func_ov035_020bb468(int index);

void LoadFadeModel(BOOL secondary) {
    FadeWork *work = data_ov035_020bc504;
    int i;
    void *file;
    int track;
    char name[16];
    int modelId = secondary ? work->modelIdB : work->modelIdA;

    if (modelId >= 0) {
        file = func_0202c4a0(ObjectManager_GetSecondEntryParam(modelId), 2);
        InitSharedRecordAndDispatchAlt(work, ObjectManager_GetFirstEntryParam(modelId), file, 2);
        for (track = 0; track < 5; track++) {
            if (work->animCounts[(u16)track] > 0) {
                selectJointAnimationBlend(work, (u16)track, work->animCounts, 0);
                func_01ffb2f8(work, (u16)track, 0);
            }
        }
        Flags16_ClearBit1(work);
        NNSi_FndFreeFromDefaultHeap(file);
        if (!secondary) {
            MaterialDict *dict;
            MaterialSet *materials;
            if (work->model != NULL && work->model->materialsOffset != 0) {
                materials = (MaterialSet *)((u8 *)work->model + work->model->materialsOffset);
            } else {
                materials = NULL;
            }
            dict = (MaterialDict *)((u8 *)materials + 4 + materials->dictOffset);
            for (i = 0; i < work->count; i++) {
                char *names;
                int count;
                int j;
                OS_SPrintf(name, data_ov035_020bc4c8, data_ov035_020bc4d0, i);
                j = 0;
                count = materials->count;
                if (j < count) {
                    names = (char *)dict + dict->namesOffset;
                    do {
                        if (strcmp(names + j * 16, name) == 0) {
                            work->entries[i].material = j;
                            break;
                        }
                    } while (++j < count);
                }
                work->entries[i].target = 0;
                work->entries[i].value = work->entries[i].target;
                func_ov035_020bb468(i);
            }
        }
        work->active = TRUE;
    }
}