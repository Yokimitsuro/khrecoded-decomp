#include "nitro/types.h"

typedef struct {
    s32 first;
    s32 second;
} TwoWordValue;

typedef struct {
    u8 pad_0000[0x65dc];
    void *records;
} Ov015Scene;

extern Ov015Scene *data_ov015_020812e0;

extern void IndexedRecord_SetPair(void *records, int recordIndex, TwoWordValue *value);
extern void IndexedRecord_SetActive(void *records, int recordIndex);

void SetSceneRecordValue(int recordIndex, TwoWordValue *value) {
    IndexedRecord_SetPair(data_ov015_020812e0->records, recordIndex, value);
    IndexedRecord_SetActive(data_ov015_020812e0->records, recordIndex);
}
