#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MotionRecord {
    int kind;
    VecFx32 start;
    VecFx32 end;
    int param0;
    int param1;
    int param2;
} MotionRecord;

void InitMotionRecord(MotionRecord *record, int param0, int param1, const VecFx32 *start, const VecFx32 *end, int param2, int kind)
{
    record->kind = kind;
    record->end = *end;
    record->start = *start;
    record->param0 = param0;
    record->param1 = param1;
    record->param2 = param2;
}
