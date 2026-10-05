#include "nitro/types.h"
#include "nitro/fx_types.h"

BOOL IsMapPointInBounds(const VecFx32 *pos)
{
    if (pos->x < 0 || pos->x > 0x100000) {
        return FALSE;
    }
    if (pos->y < 0x18000 || pos->y > 0xa8000) {
        return FALSE;
    }
    return TRUE;
}
