#include "nitro/types.h"

typedef struct ModelResList {
    u8 pad_00[0xc];
    void *texFile;
    void *tex;
} ModelResList;

typedef struct ModelInstance {
    u8 pad_00[0x74];
    ModelResList *resList;
    void *resMdl;
} ModelInstance;

typedef struct ModelAnimSet {
    u16 count[5];
    u16 texSource;
    int pad_0c;
    void **objects[5];
} ModelAnimSet;

extern void *NestedPointer_GetFirstWord(void *archive, int memberIndex, int subIndex);
extern int ReadValidatedRecordByte(void *file);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuFill8(void *dst, int value, int size);
extern void *NNS_G3dGetAnmByIdx(void *anmSet, u32 idx);
extern void *NNSi_FndGetAllocatorForDefaultHeap(void *heap);
extern void *NNS_G3dAllocAnmObj(void *allocator, void *anm, void *resMdl);
extern void *NNS_G3dGetTex(void *file);
extern void NNS_G3dAnmObjInit(void *anmObj, void *anm, void *resMdl, void *tex);

void BindModelAnimations(ModelAnimSet *set, ModelInstance *inst, void *archive, int texSource)
{
    int i;
    int total = 0;
    int j;

    for (i = 0; i < 5; i++) {
        total += ReadValidatedRecordByte(NestedPointer_GetFirstWord(archive, i, 0));
    }
    if (total > 0) {
        void **slot = NNSi_FndAllocFromDefaultHeap(total * 4);

        for (i = 0; i < 5; i++) {
            int n = ReadValidatedRecordByte(NestedPointer_GetFirstWord(archive, i, 0));
            if (n > 0) {
                set->objects[i] = slot;
                slot += n;
            } else {
                set->objects[i] = NULL;
            }
        }
    } else {
        MI_CpuFill8(set, 0, sizeof(ModelAnimSet));
    }
    for (i = 0; i < 5; i++) {
        void *anmSet = NestedPointer_GetFirstWord(archive, i, 0);
        int n = ReadValidatedRecordByte(anmSet);

        for (j = 0; j < n; j++) {
            void *anm = NNS_G3dGetAnmByIdx(anmSet, j);
            void *tex;

            set->objects[i][j] = NNS_G3dAllocAnmObj(NNSi_FndGetAllocatorForDefaultHeap(0), anm, inst->resMdl);
            if (i == 3) {
                tex = inst->resList->tex;
                if (tex == NULL) {
                    tex = NNS_G3dGetTex(NestedPointer_GetFirstWord(inst->resList->texFile, 7, 0));
                }
            } else {
                tex = NULL;
            }
            NNS_G3dAnmObjInit(set->objects[i][j], anm, inst->resMdl, tex);
        }
        set->count[i] = n;
    }
    set->texSource = texSource;
}
