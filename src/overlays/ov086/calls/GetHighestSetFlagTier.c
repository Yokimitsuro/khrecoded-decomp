#include "nitro/types.h"

typedef struct {
    int flagIds[3];
} FlagIdTable;

extern const FlagIdTable data_ov086_020c20fc;
extern BOOL func_ov001_020645c8(u32 flagId);

int GetHighestSetFlagTier(int baseFlagId)
{
    FlagIdTable table = data_ov086_020c20fc;
    int i;
    int lastSet = -1;

    for (i = 0; i < 3; i++) {
        if (func_ov001_020645c8(baseFlagId + table.flagIds[i])) {
            lastSet = i;
        }
    }
    return lastSet + 1;
}
