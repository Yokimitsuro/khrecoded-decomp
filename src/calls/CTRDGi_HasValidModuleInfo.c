#include "nitro/types.h"
#include "nitro/ctrdg.h"

extern CTRDGModuleInfo data_02fffc30;

BOOL CTRDGi_HasValidModuleInfo(void)
{
    if (data_02fffc30.moduleID.raw != 0xffff) {
        return TRUE;
    }
    return FALSE;
}
