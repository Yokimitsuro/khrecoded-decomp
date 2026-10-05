#include "nitro/types.h"

int GetRowColorWithLimit(int row, int cursor, int limit)
{
    if (cursor < 0 || row == cursor) {
        if (row >= limit) {
            return 0xa;
        }
        return 2;
    }
    if (row < cursor) {
        return 0xc;
    }
    return 8;
}