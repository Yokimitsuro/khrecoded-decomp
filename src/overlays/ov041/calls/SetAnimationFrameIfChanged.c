#include "nitro/types.h"

extern void func_01ffb12c(int object);
extern int *func_01ffb2f8(int object, int track, int frame);
extern void func_ov041_020c386c(int object, void *out, int blend);

void SetAnimationFrameIfChanged(int owner, int frame) {
    int object;

    object = *(int *)(owner + 0x3a4);
    if (((object != 0) && (*(int *)(object + 0x114) != 0)) &&
        ((*(int *)(object + 0x114) != 2 || (frame != *(int *)(object + 0x110))))) {
        func_01ffb2f8(object, 0, frame);
        *(u32 *)(object + 0x20) = *(u32 *)(object + 0x20) | 3;
        func_01ffb12c(object);
        *(u32 *)(object + 0x20) = *(u32 *)(object + 0x20) & 0xfffffffc;
        func_ov041_020c386c(object, (void *)(object + 0x118), 0);
        *(int *)(object + 0x110) = frame;
        *(u32 *)(object + 0x114) = 2;
    }
}
