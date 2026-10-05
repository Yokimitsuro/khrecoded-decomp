#include "nitro/types.h"

typedef struct PanelRecord {
    u8 data[0x1C];
} PanelRecord;

typedef struct GaugeScene {
    u8 pad_000[0x18];
    int gaugeHandle;
    u8 pad_01C[8];
    u8 stateFlags;
    u8 pad_025[0x27];
    int unitCost;
    u8 pad_050[0x78];
    u16 currentUnits;
    u8 pad_0CA[0x42];
    PanelRecord panels[2];
} GaugeScene;

typedef void (*CellDrawFunc)(int handle, int cell, int mode);

extern GaugeScene *data_ov001_020a04cc;

extern void func_ov001_02073894(int handle, int cell, int mode);
extern void func_ov001_02073d00(PanelRecord *dst, PanelRecord *src, u32 value, CellDrawFunc draw, int handle,
                                BOOL notify, int setup);

void UpdateGaugeUnits(int units)
{
    GaugeScene *scene = data_ov001_020a04cc;
    u32 remainder = (u16)(units % (scene->unitCost * 200));
    u32 value;

    if (scene->currentUnits == units) {
        return;
    }
    if (remainder == 0 && units != 0) {
        remainder = (u16)(scene->unitCost * 200);
    }
    value = (u16)(units * 0x30 / (scene->unitCost * 200));
    if (value == 0 && remainder != 0) {
        value = 1;
    }
    scene->currentUnits = units;
    func_ov001_02073d00(&scene->panels[1], &scene->panels[0], value, func_ov001_02073894, scene->gaugeHandle, FALSE, 1);
    scene->stateFlags |= 2;
}
