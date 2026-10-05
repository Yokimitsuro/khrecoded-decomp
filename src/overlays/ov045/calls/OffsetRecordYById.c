#include "nitro/types.h"

typedef struct {
    u16 id;
    s16 x;
    s16 y;
} Record;

extern Record *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b824c(void *pool, Record *record, s16 x, s16 y);

void OffsetRecordYById(void *pool, int recordId, int offsetY)
{
    Record *record = FindActiveRecordById(pool, (u16)recordId);

    func_ov027_020b824c(pool, record, record->x, record->y + offsetY);
}
