#include "nitro/types.h"

typedef struct CornerOffset {
    s32 x;
    s32 y;
} CornerOffset;

typedef struct CornerItem {
    u8 pad_00[0x10];
    CornerOffset position;
    u8 pad_18[0x18];
} CornerItem;

typedef struct TweenFlags {
    u32 started : 1;
    u32 paused : 1;
    u32 finished : 1;
    u32 reserved : 29;
} TweenFlags;

typedef struct Tween {
    s32 mode;
    s32 duration;
    s32 from;
    s32 to;
    s32 startTick[2];
    TweenFlags flags;
} Tween;

typedef struct CornerSpread {
    CornerItem items[4];
    u8 pad_0c0[0x60];
    CornerItem *center;
    s32 state;
    u8 pad_128[4];
    Tween tween;
} CornerSpread;

extern void SampleTweenValue(Tween *tween, s32 *value);
extern void PlaceCornerItems(CornerItem *items, s32 distance, const CornerOffset *center);
extern void func_ov001_0206ad28(void *list);
extern void func_02052528(Tween *tween, int mode, int from, int to, int duration);
extern void func_02052570(Tween *tween);

void UpdateCornerSpread(CornerSpread *spread, CornerOffset *center)
{
    s32 distance;

    switch (spread->state) {
    case 1:
        SampleTweenValue(&spread->tween, &distance);
        PlaceCornerItems(spread->items, distance, center);
        spread->center->position = *center;
        func_ov001_0206ad28(spread->center);
        if (spread->tween.flags.finished) {
            func_02052528(&spread->tween, 0, 0, 0x5000, 300);
            func_02052570(&spread->tween);
            spread->state = 2;
        }
        break;
    case 2:
        SampleTweenValue(&spread->tween, &distance);
        PlaceCornerItems(spread->items, distance, center);
        spread->center->position = *center;
        func_ov001_0206ad28(spread->center);
        if (spread->tween.flags.finished) {
            func_02052528(&spread->tween, 0, spread->tween.to, spread->tween.from, 300);
            func_02052570(&spread->tween);
        }
        break;
    }
}
