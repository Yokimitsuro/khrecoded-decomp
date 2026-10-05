#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x14];
    void *buffer;
    void *objects;
    u8 pad_1c[0x4];
} ObjectGroup;

typedef struct {
    u8 pad_00[0x28];
    void *buffer0;
    void *buffer1;
    void *items;
    void *buffer3;
    u8 pad_38[0x4];
} ActiveRecord;

typedef struct {
    u8 pad_00[0x4c];
    void *stepCodes;
    ActiveRecord *records;
    u8 pad_54;
    u8 recordCount;
    u8 activeGroupCount;
    u8 groupCount;
    u8 pad_58[0x8];
    void *workBuffer;
    ObjectGroup *groups;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void FreeSceneRecords(void)
{
    int i;
    int count;

    if (data_ov031_020bc820->records != NULL) {
        count = data_ov031_020bc820->groupCount;
        for (i = 0; i < count; i++) {
            NNSi_FndFreeFromDefaultHeap(data_ov031_020bc820->groups[i].buffer);
            NNSi_FndFreeFromDefaultHeap(data_ov031_020bc820->groups[i].objects);
        }
        NNSi_FndFreeFromDefaultHeap(data_ov031_020bc820->groups);
        NNSi_FndFreeFromDefaultHeap(data_ov031_020bc820->stepCodes);
        for (i = 0; i < data_ov031_020bc820->recordCount; i++) {
            NNSi_FndFreeFromDefaultHeap(data_ov031_020bc820->records[i].buffer0);
            NNSi_FndFreeFromDefaultHeap(data_ov031_020bc820->records[i].buffer1);
            NNSi_FndFreeFromDefaultHeap(data_ov031_020bc820->records[i].items);
            NNSi_FndFreeFromDefaultHeap(data_ov031_020bc820->records[i].buffer3);
        }
        NNSi_FndFreeFromDefaultHeap(data_ov031_020bc820->records);
        data_ov031_020bc820->records = NULL;
        NNSi_FndFreeFromDefaultHeap(data_ov031_020bc820->workBuffer);
    }
}
