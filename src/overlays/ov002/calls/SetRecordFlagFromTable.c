#include "nitro/types.h"

extern int LookupTableOffset(int index, int offset);
extern s32 func_ov002_02069bc8(void *flagSets, s32 recordId, BOOL value, BOOL usePrimary);

s32 SetRecordFlagFromTable(void *flagSets, int index, int offset, BOOL value, BOOL usePrimary)
{
    return func_ov002_02069bc8(flagSets, LookupTableOffset(index, offset), value, usePrimary);
}
