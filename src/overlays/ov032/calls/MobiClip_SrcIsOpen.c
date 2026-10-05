#include "nitro/types.h"

extern u32 data_ov032_020bffe0;
extern s32 Obj_GetWord28(u32 handle);

/* Checks whether the MobiClip source handle is open */
BOOL MobiClip_SrcIsOpen(void) {
    if (Obj_GetWord28(data_ov032_020bffe0) != 0) {
        return 1;
    }
    return 0;
}
