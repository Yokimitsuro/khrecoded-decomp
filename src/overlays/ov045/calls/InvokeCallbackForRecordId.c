#include "nitro/types.h"

typedef struct RecordPool RecordPool;
typedef struct Record Record;

extern Record *FindActiveRecordById(RecordPool *pool, u32 recordId);
extern void func_ov027_020b8230(RecordPool *pool, Record *record);

void InvokeCallbackForRecordId(RecordPool *pool, u32 recordId)
{
    Record *record = FindActiveRecordById(pool, (u16)recordId);
    func_ov027_020b8230(pool, record);
}
