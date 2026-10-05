#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Spawner Spawner;

struct Spawner {
    u8 pad_00[8];
    void *owner;
    u8 pad_0c[8];
    void (*update)(Spawner *spawner);
    u8 pad_18[0x40];
    s32 finished;
    u8 pad_5c[0x18];
    fx32 velocityY;
    u8 pad_78[0x10];
    fx32 height;
    fx32 positionY;
    fx32 startHeight;
    fx32 endHeight;
    fx32 sink;
    fx32 elapsed;
};

extern void func_ov001_02085054(void *owner, Spawner *spawner);
extern fx32 EaseProgress(fx32 value, fx32 range, int mode);
extern void func_ov001_020850e4(Spawner *spawner);
extern void func_ov001_02085348(Spawner *spawner, BOOL falling);

int UpdateSpawnerRise(Spawner *spawner)
{
    fx32 height;
    fx32 ratio;

    func_ov001_02085054(spawner->owner, spawner);
    spawner->velocityY -= 0x52;
    height = spawner->elapsed += 0x1000;
    if (height >= 0x3c000) {
        spawner->finished = 1;
        spawner->update = func_ov001_020850e4;
        height = spawner->endHeight;
    } else {
        ratio = EaseProgress(height, 0x3c000, 1);
        height = (fx32)(((s64)spawner->startHeight * (0x1000 - ratio) + 0x800) >> 12)
               + (fx32)(((s64)spawner->endHeight * ratio + 0x800) >> 12);
    }
    spawner->height = height;
    if (spawner->sink != 0) {
        spawner->sink -= 0x1a;
        if (spawner->sink < 0) {
            spawner->sink = 0;
        }
    }
    spawner->positionY -= spawner->sink;
    func_ov001_02085348(spawner, spawner->velocityY < 0);
    return 0;
}

