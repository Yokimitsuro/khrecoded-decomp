#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TargetMarker {
    u8 pad0[8];
    u8 bounds[8];
    s8 targetIndex;
    s8 active;
    u8 pad12[2];
    int elapsed;
    fx32 heightOffset;
    u8 pad1C[4];
    int hit;
    int useOverride;
} TargetMarker;

extern VecFx32 *func_ov001_0206dc4c(int index);
extern VecFx32 *func_ov001_0206dc60(int index);
extern int ProjectWorldToScreenFx(VecFx32 *position, void *bounds);

void UpdateTrackedTargetMarker(TargetMarker *marker, int step) {
    VecFx32 *source;
    VecFx32 position;

    if (marker->active != 0) {
        if (marker->useOverride != 0) {
            source = func_ov001_0206dc60(marker->targetIndex);
        } else {
            source = func_ov001_0206dc4c(marker->targetIndex);
        }
        if (source != NULL) {
            position = *source;
            position.y += marker->heightOffset;
            if (ProjectWorldToScreenFx(&position, marker->bounds) >= 0) {
                marker->hit = 1;
            }
        }
        marker->elapsed += step;
        if (marker->elapsed >= 0x3000) {
            marker->active = 0;
        }
    }
}
