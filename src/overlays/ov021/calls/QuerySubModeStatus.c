#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56c0;

extern int Camera_GetDriftHeading(void);
extern int func_ov042_020bd4cc(void);
extern int GetCameraYaw(void);

int QuerySubModeStatus(void)
{
    switch (data_ov021_020b56c0->mode) {
    case 0:
        return Camera_GetDriftHeading();
    case 1:
        return func_ov042_020bd4cc();
    case 2:
        return GetCameraYaw();
    case 3:
        return 0;
    }
    return 0;
}
