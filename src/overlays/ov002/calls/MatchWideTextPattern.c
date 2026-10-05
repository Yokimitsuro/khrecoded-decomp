#include "nitro/types.h"

BOOL MatchWideTextPattern(const u16 *text, const u16 *pattern, int length)
{
    int i;

    for (i = 0; i < length; i++) {
        u16 expected = pattern[i];
        u16 actual = text[i];

        if (actual == expected) {
            continue;
        }
        if (actual == '@' && (expected == 'a' || expected == 'o')) {
            continue;
        }
        if (expected == '$' && !((actual >= '0' && actual <= '9') || (actual >= 'A' && actual <= 'Z')
                                 || (actual >= 'a' && actual <= 'z') || (actual >= 0xa0 && actual <= 0xff)
                                 || (actual >= 0x3041 && actual <= 0x30ff))) {
            continue;
        }
        return FALSE;
    }
    return TRUE;
}
