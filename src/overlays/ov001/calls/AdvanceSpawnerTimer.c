#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SpawnedObject {
    u8 pad_00[0x58];
    void *owner;
} SpawnedObject;

typedef struct FieldObject {
    u8 pad_00[0x5e];
    u16 frameCounter;
} FieldObject;

typedef struct Spawner {
    u8 pad_00[0x46];
    u16 childCount;
    u8 pad_48[0x40];
    fx32 spawnInterval;
    fx32 spawnTimer;
    u16 lastFrame;
} Spawner;

extern SpawnedObject *GetStridedBufferEntry(Spawner *spawner, int index);
extern void StartSpinningActor(SpawnedObject *object);

void AdvanceSpawnerTimer(Spawner *spawner, FieldObject *object)
{
    int count;
    int i;

    object->frameCounter++;
    if (spawner->lastFrame != object->frameCounter) {
        spawner->lastFrame = object->frameCounter;
        spawner->spawnTimer += 0x1000;
        if (spawner->spawnTimer >= spawner->spawnInterval) {
            count = spawner->childCount;
            for (i = 0; i < count; i++) {
                SpawnedObject *child = GetStridedBufferEntry(spawner, i);

                if (child != NULL && child->owner == NULL) {
                    StartSpinningActor(child);
                    spawner->spawnTimer = 0;
                    return;
                }
            }
            spawner->spawnTimer = spawner->spawnInterval;
        }
    }
}
