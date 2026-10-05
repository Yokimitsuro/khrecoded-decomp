#include "nitro/types.h"

typedef struct {
    s16 values[17];
} KindTable;

extern const KindTable data_ov021_020b4e5c;
extern const KindTable data_ov021_020b4e80;
extern const KindTable data_ov021_020b4ea4;

int LookupKindTableValue(u32 kind, int index)
{
    KindTable primary;
    KindTable secondary;
    KindTable tertiary;
    int result = -1;

    switch (kind) {
    case 0:
    case 3:
        primary = data_ov021_020b4e5c;
        if (index <= 17) {
            result = primary.values[index];
        }
        break;
    case 2:
        secondary = data_ov021_020b4e80;
        if (index <= 17) {
            result = secondary.values[index];
        }
        break;
    case 1:
        tertiary = data_ov021_020b4ea4;
        if (index <= 17) {
            result = tertiary.values[index];
        }
        break;
    }
    return result;
}
