#include "nitro/types.h"

extern int data_ov034_020be940;
extern u32 Obj_GetWord28(u32 handle);

/* Checks whether the MobiClip source handle is open */
BOOL MobiClip_SrcIsOpen_020bde70(void) {
    u32 status = Obj_GetWord28(data_ov034_020be940);
    if (status != 0) {
        return 1;
    }
    return 0;
}
