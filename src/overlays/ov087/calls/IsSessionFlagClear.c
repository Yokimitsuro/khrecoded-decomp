#include "nitro/types.h"

extern BOOL func_ov001_020645c8(u32 value);
extern const int data_ov087_020c7cf0[3];

typedef struct {
    int values[3];
} FlagBaseTable;

BOOL IsSessionFlagClear(void *scene, int index)
{
    FlagBaseTable table = *(const FlagBaseTable *)data_ov087_020c7cf0;

    return func_ov001_020645c8(table.values[index] + 0xf50) == FALSE;
}
