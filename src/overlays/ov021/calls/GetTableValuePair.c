#include "nitro/types.h"

typedef struct {
    s32 values[3];
} ValueTriple;

extern const ValueTriple data_ov021_020b4e50;
extern const ValueTriple data_ov021_020b4e44;

void GetTableValuePair(s32 *outFirst, s32 *outSecond, int index)
{
    ValueTriple first = data_ov021_020b4e50;
    ValueTriple second = data_ov021_020b4e44;

    if (outFirst != NULL) {
        *outFirst = first.values[index];
    }
    if (outSecond != NULL) {
        *outSecond = second.values[index];
    }
}
