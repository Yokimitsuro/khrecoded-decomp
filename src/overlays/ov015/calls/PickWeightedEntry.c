#include "nitro/types.h"

typedef struct WeightedEntry {
    s8 value;
    s8 weight;
} WeightedEntry;

extern unsigned int func_0202a9e4(unsigned int range);

int PickWeightedEntry(const WeightedEntry *entries, int count)
{
    int i;
    int total = 0;
    int roll;

    for (i = 0; i < count; i++) {
        total += entries[i].weight;
    }
    roll = func_0202a9e4((u16)total);
    for (i = 0; i < count; i++) {
        roll -= entries[i].weight;
        if (roll < 0) {
            break;
        }
    }
    return i;
}
