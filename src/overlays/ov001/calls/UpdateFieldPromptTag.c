#include "nitro/types.h"

typedef struct RecordPool RecordPool;

extern BOOL IsModeSetOrFlag370aClear(void);
extern BOOL IsHudFlag7Set(void);
extern BOOL IsFieldFlag10Set(void);
extern void *FindActiveRecordById(RecordPool *pool, u32 recordId);
extern void func_ov027_020b824c(RecordPool *pool, void *record, u16 first, u16 second);
extern void func_ov027_020b82a4(RecordPool *pool, void *record, int visible);
extern void func_ov027_020b8230(RecordPool *pool, void *record);

void UpdateFieldPromptTag(int unused, RecordPool *pool)
{
    void *record;

    if (!IsModeSetOrFlag370aClear() || IsHudFlag7Set() || IsFieldFlag10Set()) {
        func_ov027_020b824c(pool, FindActiveRecordById(pool, 0x1f), 0, 0x14);
    } else {
        record = FindActiveRecordById(pool, 0x1f);
        func_ov027_020b82a4(pool, record, 1);
        func_ov027_020b8230(pool, record);
    }
}
