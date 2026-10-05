#include "nitro/types.h"

typedef struct {
    int values[8];
} FrameTable;

typedef struct {
    u8 pad_00[0xc];
    u16 rawData[1];
} ScreenData;

typedef struct {
    u8 pad_00[8];
    ScreenData *screen;
} ScreenResource;

typedef struct {
    u8 pad_000[0xbd];
    s8 frame;
    s8 delay;
    u8 pad_0bf[0x5f8 - 0xbf];
    u8 resources[1];
} AnimState;

extern AnimState *data_ov015_0207e960;
extern const FrameTable data_ov015_0207a09c;
extern const FrameTable data_ov015_0207a0bc;
extern const FrameTable data_ov015_0207a0fc;
extern ScreenResource *func_ov027_020b8578(void *owner, int entryId);
extern void GXS_LoadBG1Scr(const void *src, u32 offset, u32 size);

void AnimateSubBg1Screen(void)
{
    FrameTable mainScreens;
    FrameTable sideScreens;
    FrameTable nextFrames;
    int i;
    ScreenResource *resource;

    mainScreens = data_ov015_0207a09c;
    sideScreens = data_ov015_0207a0bc;
    nextFrames = data_ov015_0207a0fc;
    if (data_ov015_0207e960->delay == 0) {
        data_ov015_0207e960->frame = nextFrames.values[data_ov015_0207e960->frame];
        resource = func_ov027_020b8578(data_ov015_0207e960->resources, (u16)mainScreens.values[data_ov015_0207e960->frame]);
        for (i = 0; i < 10; i++) {
            GXS_LoadBG1Scr(resource->screen->rawData + i * 12, (i + 6) * 0x40, 0x18);
        }
        resource = func_ov027_020b8578(data_ov015_0207e960->resources, (u16)sideScreens.values[data_ov015_0207e960->frame]);
        for (i = 0; i < 2; i++) {
            GXS_LoadBG1Scr(resource->screen->rawData + i * 7, i * 0x40 + 0x1a, 0xe);
        }
        data_ov015_0207e960->delay = 2;
    } else {
        data_ov015_0207e960->delay--;
    }
}
