#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);
extern const VecFx32 *func_ov001_0206dc4c(int arg);

BOOL IsEntityWithinRange(int entity) {
    if (0 < *(int *)(entity + 0x34)) {
        const VecFx32 *reference = func_ov001_0206dc4c(0);
        fx32 distance = VEC_Distance(reference, (const VecFx32 *)(entity + 0x38));
        if (*(int *)(entity + 0x34) < distance) {
            return 0;
        }
    }
    return 1;
}
