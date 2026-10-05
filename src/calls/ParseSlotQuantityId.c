#include "nitro/types.h"

extern int strlen(const char *s);

char *ParseSlotQuantityId(void *world, char *name)
{
    int i;
    int count;
    int quantity;
    int kind;
    int slot;
    int value;

    if (name[1] == ':' && (kind = name[0]) >= '0' && kind <= '3') {
        quantity = 0;
        slot = kind - '0';
        count = strlen(name) - 2;
        for (i = 0; i < count; i++) {
            quantity = quantity * 10 + (name[i + 2] - '0');
        }
        value = *(int *)((char *)world + slot * 4 + 0x58);
        return (char *)((quantity & 0x1ff) | (0x80000000 | (((value + 0x8000) & 0xfffffc) << 7)));
    }
    return name;
}
