#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 *data_ov059_020cffc4;
extern fx32 func_ov031_020bc060(void);
extern fx32 GetField28(void);
extern fx32 GetSeekStep(void);
extern fx32 FX_Div(fx32 numer, fx32 denom);

int GetStateTransitionDelay(u32 from, u32 to) {
    int result = 0;

    if (from == to || to == (u32)-1) {
        return 0;
    }
    switch (from) {
    case 2:
        result = 5;
        break;
    case 3:
        if (to == 10) {
            result = 15;
        } else if (*(int *)(data_ov059_020cffc4 + 0x768) == 0) {
            result = 5;
        }
        break;
    case 0:
    case 1: {
        fx32 diff = func_ov031_020bc060() - GetField28();
        if (diff != 0) {
            result = FX_Div(diff, GetSeekStep()) >> 12;
        } else if (to != 3) {
            if (to <= 1) {
                result = 10;
            } else {
                result = 5;
            }
        } else {
            result = 3;
        }
        break;
    }
    case 10:
    case 12:
        result = 5;
        break;
    }
    return result;
}
