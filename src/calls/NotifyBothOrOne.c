#include "nitro/types.h"

extern void func_02001044(u32 a, u32 b, int index);

void NotifyBothOrOne(u32 a, u32 b, int index) {
    int i;

    if (index < 0) {
        i = 0;
        do {
            func_02001044(a, b, i);
            i = i + 1;
        } while (i < 2);
        return;
    }
    func_02001044(a, b, index);
}
