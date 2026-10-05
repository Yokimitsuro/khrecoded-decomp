#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x138];
    int defaultPage;
} Ov086Menu;

extern Ov086Menu *data_ov086_020c3020;
extern BOOL func_ov001_020645c8(u32 value);

BOOL IsRecordPageUnavailable(int page)
{
    Ov086Menu *menu = data_ov086_020c3020;

    if ((page == 7 && !func_ov001_020645c8(0xa12)) || (page != 7 && page == menu->defaultPage))
    {
        return TRUE;
    }
    return FALSE;
}
