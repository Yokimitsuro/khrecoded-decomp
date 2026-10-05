#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x5c];
    u16 nearestEvent;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern VecFx32 *func_ov001_0206dc4c(int index);
extern u16 ForwardToActiveServiceWithResult(void);
extern u16 func_ov001_0208796c(u16 id);
extern BOOL IsStageEventReady(u16 id);
extern int QueryStageEventPlacement(u16 id, int arg, VecFx32 *position, u16 *direction);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);

void FindNearestStageEvent(void)
{
    VecFx32 *origin = func_ov001_0206dc4c(0);
    fx32 best = 0x7fffffff;
    u16 id;
    u16 next;
    u16 prev;
    VecFx32 position;
    fx32 distance;
    int found;

    data_ov031_020bc820->nearestEvent = 0xffff;
    for (id = ForwardToActiveServiceWithResult(); id != 0; id = func_ov001_0208796c(id)) {
        if (IsStageEventReady(id)) {
            prev = 0;
            found = QueryStageEventPlacement(id, 0, &position, &next);
            while (found) {
                distance = VEC_Distance(&position, origin);
                if (best > distance) {
                    best = distance;
                    data_ov031_020bc820->nearestEvent = id;
                }
                if (prev >= next) {
                    break;
                }
                prev = next;
                found = QueryStageEventPlacement(id, next, &position, &next);
            }
        }
    }
}


