#include "nitro/types.h"

extern int CheckStatusAndThreshold();

int GetRowColorWithStatus(int row, int cursor, int limit)
{
    if (cursor < 0 || row == cursor) {
        if (row >= limit) {
            return 0xa;
        }
        if (CheckStatusAndThreshold() >= 2) {
            return 0xe;
        }
        return 2;
    }
    if (row < cursor) {
        return 0xc;
    }
    return 8;
}