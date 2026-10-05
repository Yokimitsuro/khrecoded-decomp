#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ProximityTrigger {
    u8 pad_00[0x74];
    fx32 radius;
    VecFx32 position;
} ProximityTrigger;

extern int func_ov001_0206dc38(void);
extern VecFx32 *func_ov001_0206dc4c(int slot);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);

BOOL IsLeadActorWithinRadius(ProximityTrigger *trigger)
{
    if (func_ov001_0206dc38() > 0) {
        if (trigger->radius >= VEC_Distance(&trigger->position, func_ov001_0206dc4c(0))) {
            return TRUE;
        }
    }
    return FALSE;
}
