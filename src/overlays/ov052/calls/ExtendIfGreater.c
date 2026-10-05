#include "nitro/types.h"

/* Raises a field to a new floor value */
void ExtendIfGreater(int entity, int minValue)
{
    if (*(int *)(entity + 0x9f8) < minValue) {
        *(int *)(entity + 0x9f8) = minValue;
    }
}
