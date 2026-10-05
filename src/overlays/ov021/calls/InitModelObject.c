#include "nitro/types.h"

typedef struct {
    u16 unk_00;
    u16 loaded;
} SharedRecord;

typedef struct {
    u8 state;
    s8 slot;
    u8 pad_002[6];
    u8 body[0x108];
    u16 mask;
    u8 pad_112[0xa];
    u32 unk_11c;
} ModelObject;

extern SharedRecord *SND_RegisterSeq(int a, int b);
extern void *func_0202c4a0(u32 fileId, u32 mode);
extern void func_0202edb0(void *object, SharedRecord *record, void *data, int kind);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void InitModelObject(ModelObject *model, int recordId, u32 fileId)
{
    void *data;
    SharedRecord *record;

    model->slot = -1;
    data = NULL;
    model->state = 0;
    model->mask = 0x1f;
    model->unk_11c = 0;
    record = SND_RegisterSeq(recordId, 6);
    if (record->loaded == 0) {
        data = func_0202c4a0(fileId, 0x11);
    }
    func_0202edb0(model->body, record, data, 6);
    if (data != NULL) {
        NNSi_FndFreeFromDefaultHeap(data);
    }
}
