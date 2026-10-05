#include "nitro/types.h"

typedef struct PhaseObject PhaseObject;

struct PhaseObject {
    u8 pad_00[0x64];
    int phase;
    u8 pad_68[8];
    void (*callback)(PhaseObject *object);
};

extern s64 _s32_div_f(int numerator, int denominator);

int AdvanceWrappedPhase(PhaseObject *object)
{
    if (object->callback != NULL) {
        object->callback(object);
    }
    object->phase += 0x11d;
    object->phase = _s32_div_f(object->phase, 0x6488) >> 32;
    return 0;
}
