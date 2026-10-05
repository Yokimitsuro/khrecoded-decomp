#include "nitro/types.h"

typedef struct {
    int words[4];
} Block16;

extern Block16 *func_ov052_020ca330(Block16 *block);

int CopyActiveBlockIfPresent(int entity, Block16 *out)
{
    int active = *(int *)(entity + 0x1dc);
    func_ov052_020ca330(out);
    if (active != 0) {
        *out = *(Block16 *)(entity + 0x105c);
    }
    return active;
}
