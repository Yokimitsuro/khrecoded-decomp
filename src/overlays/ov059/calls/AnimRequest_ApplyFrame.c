#include "nitro/types.h"

typedef struct {
    s32 kind;
    u8 pad_04[0x1c];
    s32 frame;
} AnimRequest;

extern int *func_01ffb2f8(void *anim, int channel, int frame);

void AnimRequest_ApplyFrame(AnimRequest *request, void *anim)
{
    switch (request->kind) {
    case 1:
    case 2:
    case 3:
        func_01ffb2f8(anim, 0, request->frame);
        func_01ffb2f8(anim, 2, request->frame);
        break;
    case 4:
        func_01ffb2f8(anim, 0, request->frame);
        break;
    }
}
