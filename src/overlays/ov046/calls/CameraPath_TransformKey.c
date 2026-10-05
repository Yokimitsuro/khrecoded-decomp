#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CameraPathKey {
    VecFx32 position;
    VecFx32 target;
    VecFx32 up;
    u8 pad_24[0x1c];
    s32 targetIsDirection : 1;
} CameraPathKey;

typedef struct EventCameraWork {
    u8 pad_00[0x128];
    MtxFx33 rotation;
    VecFx32 translation;
} EventCameraWork;

extern void func_01ff9404(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void CameraPath_TransformKey(EventCameraWork *work, CameraPathKey *key)
{
    func_01ff9404(&key->position, &work->rotation, &key->position);
    func_01ff9404(&key->up, &work->rotation, &key->up);
    if (key->targetIsDirection) {
        func_01ff9404(&key->target, &work->rotation, &key->target);
    } else {
        func_01ff9404(&key->target, &work->rotation, &key->target);
        VEC_Add(&key->target, &work->translation, &key->target);
    }
    VEC_Add(&key->position, &work->translation, &key->position);
}
