#include "nitro/types.h"

typedef void (*HudCallback)(void);

typedef struct HudResource {
    u8 pad_00[0xc];
    u32 value0C;
    u32 value10;
    u32 value14;
} HudResource;

typedef struct HudSetup {
    u32 unk_00;
    HudResource *gauge;
    HudResource *extra;
} HudSetup;

typedef struct GaugeParams {
    u16 widths[3];
    u16 heights[3];
    u32 resource;
} GaugeParams;

typedef struct FieldHud {
    u8 pad_000[0x414];
    void *gaugeWidget;
    void *portraitWidget;
    void *frameWidget;
    void *timerWidget;
    void *counterWidget;
    void *statusWidget;
    u8 pad_42C[0x4];
    void *extraWidget;
    u8 pad_434[0x4];
    void *overlayWidget;
    u8 pad_43C[0x1cc];
    s32 memberIds[3];
    u8 pad_614[0xd2c];
    HudCallback promptCallbacks[6];
} FieldHud;

extern u8 data_ov027_020ba3b4[];
extern u8 data_ov027_020ba3a0[];
extern u8 data_ov001_0209ee4c[];
extern u8 data_ov001_0209eebc[];
extern u8 data_ov001_0209ef10[];
extern u8 data_ov001_0209ef58[];
extern u8 data_ov001_0209efb4[];
extern u8 data_ov001_0209f010[];

extern u8 *GetOverlaySelectionRecord(int index);
extern void *func_0202a45c(void *descriptor, void *userData);
extern void MI_CpuFill8(void *dst, int val, u32 size);
extern unsigned int MakePrimaryVramKey(unsigned int slot);
extern void *func_0202c4a0(unsigned int fileId, int heapId);
extern void NNS_G2dGetUnpackedBGCharacterData(void *file, HudResource **out);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void OpenArrowPrompt(void);
extern void ResetMenuScreenLayers(void);
extern void ArrowPrompt_HandleDpad(void);
extern void func_ov001_0207e0bc(void);
extern void func_ov001_0207e0c8(void);
extern void func_ov001_0207e0d4(void);

void CreateFieldHudWidgets(FieldHud *hud, HudSetup *setup)
{
    int scene = *(s16 *)(GetOverlaySelectionRecord(0) + 0x130);
    u32 resource;
    HudResource *graphic;
    GaugeParams params;
    void *file;
    int i;

    hud->frameWidget = func_0202a45c(data_ov027_020ba3b4, NULL);
    MI_CpuFill8(&params, 0, sizeof(GaugeParams));
    params.widths[0] = 0x3c;
    params.heights[0] = 0x3c;
    for (i = 1; i < 3; i++) {
        if (hud->memberIds[i] != -1) {
            params.widths[i] = 0x3c;
            params.heights[i] = 0x3c;
        }
    }
    params.resource = setup->gauge->value14;
    hud->gaugeWidget = func_0202a45c(data_ov001_0209ee4c, &params);
    file = func_0202c4a0(MakePrimaryVramKey(0xc), 0xe);
    NNS_G2dGetUnpackedBGCharacterData(file, &graphic);
    resource = graphic->value14;
    hud->portraitWidget = func_0202a45c(data_ov001_0209eebc, &resource);
    NNSi_FndFreeFromDefaultHeap(file);
    hud->timerWidget = func_0202a45c(data_ov001_0209ef10, NULL);
    hud->counterWidget = func_0202a45c(data_ov001_0209ef58, NULL);
    hud->statusWidget = func_0202a45c(data_ov001_0209efb4, NULL);
    switch (scene) {
    case 0xc4:
        hud->promptCallbacks[0] = OpenArrowPrompt;
        hud->promptCallbacks[1] = ResetMenuScreenLayers;
        hud->promptCallbacks[2] = ArrowPrompt_HandleDpad;
        hud->promptCallbacks[3] = func_ov001_0207e0bc;
        hud->promptCallbacks[4] = func_ov001_0207e0c8;
        hud->promptCallbacks[5] = func_ov001_0207e0d4;
    case 0xc5:
    case 0xc6:
    case 0xca:
        hud->extraWidget = func_0202a45c(data_ov001_0209f010, (void *)setup->extra->value0C);
    default:
        hud->overlayWidget = func_0202a45c(data_ov027_020ba3a0, NULL);
        break;
    }
}
