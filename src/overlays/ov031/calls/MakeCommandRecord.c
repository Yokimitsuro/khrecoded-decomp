#include "nitro/types.h"

typedef struct {
    u32 status;
    u32 arg0;
    u32 arg1;
    u32 arg2;
    u8 flag;
    u8 done;
} CommandRecord;

CommandRecord MakeCommandRecord(u32 arg0, u32 arg1, u32 arg2, u8 flag)
{
    CommandRecord record;

    record.status = 0;
    record.arg0 = arg0;
    record.arg1 = arg1;
    record.arg2 = arg2;
    record.flag = flag;
    record.done = 0;
    return record;
}
