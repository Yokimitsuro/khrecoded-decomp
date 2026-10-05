#include "nitro/types.h"

typedef struct SpawnPoint {
    u8 data[0xc];
} SpawnPoint;

SpawnPoint *ClaimNthFreeSpawnPoint(int target, int count, SpawnPoint *points, u8 *used)
{
    int i;
    int freeIndex;

    for (i = 0, freeIndex = 0; i < count; i++) {
        if (used[i] == 0 && freeIndex++ == target) {
            used[i] = 1;
            return &points[i];
        }
    }
    return NULL;
}
