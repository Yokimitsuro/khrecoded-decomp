#include "nitro/types.h"

typedef struct {
    u32 file;
    u32 palette;
    u32 pad_08;
    u32 userValue;
    s32 partMask;
    u32 hasExtra;
} ModelSetupDesc;

typedef struct {
    u8 data[0x2c];
} ModelPart;

typedef struct {
    u32 flags;
    u32 pad_04;
    u8 model[0x78];
    void *modelData;
    u8 pad_84[0x8c];
    u32 userValue;
    ModelPart parts[6];
    u8 pad_21c[0xc];
    void *extra;
    s8 heapId;
} ModelObject;

extern u32 MakeVramUploadParams(u32 file, u32 palette);
extern u32 MakePaletteUploadParams20(u32 file, u32 palette);
extern s32 MakePaletteUploadParams230(s32 part, u32 palette);
extern void *SND_RegisterSeq(s32 key, s32 context);
extern void *func_0202c4a0(u32 id, s32 mode);
extern void func_0202edb0(void *model, void *record, void *block, s32 context);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void NNS_G3dMdlSetMdlPolygonIDAll(void *model, s32 id);
extern void func_0202f5a4(void *model, s32 value);
extern void Obj_SetHalfwordFC(void *model, s32 value);
extern void AcquireSharedRecordState(void *state, s32 key, void *model, s32 context);
extern void LoadModelSetSlots(ModelObject *obj, ModelSetupDesc *desc);
extern void LoadSlotModelObject(void *extra, ModelSetupDesc *desc, s32 heapId);

void LoadModelObject(ModelObject *obj, ModelSetupDesc *desc)
{
    s32 context = obj->heapId + 8;
    if (!(obj->flags & 1)) {
        void *record;
        void *block;
        obj->flags |= 1;
        obj->userValue = desc->userValue;
        record = SND_RegisterSeq(MakeVramUploadParams(desc->file, desc->palette), context);
        block = func_0202c4a0(MakePaletteUploadParams20(desc->file, desc->palette), 0x11);
        func_0202edb0(obj->model, record, block, context);
        NNSi_FndFreeFromDefaultHeap(block);
        NNS_G3dMdlSetMdlPolygonIDAll(obj->modelData, 0x3f);
        func_0202f5a4(obj->model, 1);
        Obj_SetHalfwordFC(obj->model, 0x7fff);
        if (desc->partMask > 0) {
            BOOL any = FALSE;
            int i;
            for (i = 0; i < 6; i++) {
                if ((1 << i) & desc->partMask) {
                    s32 part = i;
                    if (i == 5 && (desc->partMask & 0x80)) {
                        part = i + 1;
                    }
                    AcquireSharedRecordState(&obj->parts[i], MakePaletteUploadParams230(part, desc->palette), obj->model, context);
                    any = TRUE;
                }
            }
            if (any) {
                obj->flags |= 4;
            }
        }
        if (!(desc->partMask & 0x100)) {
            LoadModelSetSlots(obj, desc);
        }
        if (desc->hasExtra) {
            obj->extra = NNSi_FndAllocFromDefaultHeap(0x114);
            LoadSlotModelObject(obj->extra, desc, obj->heapId);
        }
    }
}
