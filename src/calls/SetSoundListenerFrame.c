#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SoundListenerWork {
    u8 pad_00000[0xb4500];
    VecFx32 position;
    VecFx32 axis;
} SoundListenerWork;

extern SoundListenerWork *data_0206084c;
extern void func_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);

void SetSoundListenerFrame(const VecFx32 *position, const VecFx32 *forward, const VecFx32 *up)
{
    SoundListenerWork *work = data_0206084c;
    VecFx32 cross;

    func_01ff9ea8(forward, up, &cross);
    func_01ffaff4(&cross, &work->axis);
    work->position = *position;
}
