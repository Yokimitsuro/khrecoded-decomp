#include "nitro/types.h"

extern void MIi_CpuCopy16(const void *src, void *dest, u32 size);
extern void func_01ff86b8(const void *src, void *dest, u32 size);

void MI_CpuMove16(const void *src, void *dest, u32 size) {
    if ((u32)dest <= (u32)src || (u32)src + size <= (u32)dest) {
        MIi_CpuCopy16(src, dest, size);
    } else {
        func_01ff86b8(src, dest, size);
    }
}
