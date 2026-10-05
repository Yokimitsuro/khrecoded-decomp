#include "nitro/types.h"

typedef int (*StateQuery)(int entity);

void MarkStateThreeFlag(int entity)
{
    int state;
    StateQuery query = *(StateQuery *)(entity + 0x22c);
    if (query != NULL) {
        state = query(entity);
    } else {
        state = *(int *)(entity + 0x1dc);
    }
    if (state == 3 && (*(u8 *)(entity + 0x1064) & 0x10)) {
        *(u8 *)(entity + 0x1064) |= 0x20;
    }
}
