#include "nitro/types.h"

typedef struct GaugeSlot {
    u64 start;
    u64 interval;
    int active;
    int phase;
} GaugeSlot;

typedef struct CountPair {
    u16 total;
    u16 count;
    u16 pad;
} CountPair;

typedef struct PresetRow {
    int scale;
    int field04;
    int field08;
} PresetRow;

typedef struct GaugeScene {
    void *handles[0x2d];
    CountPair counts[4];
    u8 pad_0cc[0xf2 - 0xcc];
    u16 mainCount;
} GaugeScene;

typedef void (*GaugeDrawFn)(void *context, int index, int mode);

extern GaugeScene *data_ov001_020a04cc;
extern PresetRow data_ov001_0209edf8[];
extern u64 OS_GetTick(void);
extern void DrawShortLayoutRow(void *context, int index, int mode);
extern void func_ov001_02073870(void *context, int index, int mode);
extern void RunMenuEntryCallbacks(void *context, int menu, int count, GaugeDrawFn callback, int mode);

int AdvanceGaugeSlot(int index, GaugeSlot *slot)
{
    GaugeScene *scene = data_ov001_020a04cc;
    u64 now = OS_GetTick();
    int result;
    int value;
    GaugeDrawFn draw;
    u16 count;

    result = 0;
    if (slot->active == 0) {
        return result;
    }
    if (slot->interval > now - slot->start) {
        goto done;
    }
    slot->phase ^= 1;
    if (index == 0) {
        value = scene->mainCount;
        if (value == 0 && scene->counts[0].count != 0) {
            value = 1;
        }
        draw = DrawShortLayoutRow;
    } else {
        count = scene->counts[index].count;
        value = (u16)(count * data_ov001_0209edf8[index].scale / scene->counts[index].total);
        if (value == 0 && count != 0) {
            value = 1;
        }
        draw = func_ov001_02073870;
    }
    RunMenuEntryCallbacks(scene->handles[index], index, value, draw, slot->phase != 0 ? 0 : 2);
    slot->start = now;
    result = 1;
done:
    return result;
}
