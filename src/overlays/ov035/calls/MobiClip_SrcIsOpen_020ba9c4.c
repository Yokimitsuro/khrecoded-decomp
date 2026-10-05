#include "nitro/types.h"

extern u32 data_ov035_020bc480;
extern u32 Obj_GetWord28(u32 handle);

BOOL MobiClip_SrcIsOpen_020ba9c4(void) {
    if (Obj_GetWord28(data_ov035_020bc480) != 0) {
        return 1;
    }
    return 0;
}
