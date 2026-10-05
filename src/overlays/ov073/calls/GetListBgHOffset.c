#include "nitro/types.h"

typedef struct ListView {
    u8 pad_00[0x94];
    int scrollX;
} ListView;

int GetListBgHOffset(ListView *list)
{
    return -list->scrollX;
}
