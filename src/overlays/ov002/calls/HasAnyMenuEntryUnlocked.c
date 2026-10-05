#include "nitro/types.h"

extern int DispatchContextCommand(int kind, int index, int arg2, int arg3);

BOOL HasAnyMenuEntryUnlocked(void)
{
    int i = 0;
    int count = DispatchContextCommand(1, 0, 0, 0);
    int number;

    count = count + (count + (count + 1) / 10 + 1) / 10;
    for (; i < count; i++) {
        number = i + 1;
        if (number % 10 != 0) {
            if (DispatchContextCommand(0xb, i - number / 10, 0, 0)) {
                return TRUE;
            }
        } else if (DispatchContextCommand(9, number, 0, 0)) {
            return TRUE;
        }
    }
    return FALSE;
}
