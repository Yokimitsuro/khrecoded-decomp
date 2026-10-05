#include "nitro/types.h"

typedef struct Words4 {
    u32 words[4];
} Words4;

typedef struct Words5 {
    u32 words[5];
} Words5;

typedef struct BgLayerDesc {
    Words4 *layout;
    int count;
    u16 width;
    u16 height;
    int flags;
} BgLayerDesc;

typedef struct BoardState {
    int resourceA;
    int resourceB;
    void *widget;
    char widgetData[0x28 - 0xc];
    char animSet[0x74 - 0x28];
    char objectSet[0x64f8 - 0x74];
    int active;
    char pad64fc[0x655c - 0x64fc];
    int markerSlots[4];
    int cellIds[0x12];
    int itemSlots[30];
    int cursorSlot;
    int targetSlot;
    int nodeIds[0x28];
    int pad66d4;
    int hintSlot;
    int goalSlot;
    int useChannel;
    char pad66e4[0x66ec - 0x66e4];
    int showTutorial;
} BoardState;

typedef struct BoardGlobals {
    BoardState *state;
    int unk04;
    void *cursor;
} BoardGlobals;

#define BOARD_VRAM_KEY(base) ((((base) + 0x8000) & 0xfffffc) << 7)

extern Words4 data_ov024_020b7350;
extern Words4 data_ov024_020b7360;
extern Words5 data_ov024_020b7370;
extern BoardGlobals data_ov024_020b7540;
extern int data_ov024_020b754c[6];
extern char sOv024_UiBtlBtluiP2_020b74f4[];
extern char sOv024_UiBtlBtlLanguageP2_020b7508[];

extern BoardState *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dest, int value, int size);
extern void MIi_CpuClear32(int value, void *dest, int size);
extern BOOL func_ov001_020645c8(int flag);
extern BOOL IsFieldFlag13OrSessionFlagSet(void);
extern void func_ov001_0207b228(void (*callback)(void));
extern void SetupSubScreenBgLayers(void);
extern void SetPanelSessionActive(void);
extern void *func_ov001_0207123c(void);
extern void InitTileTableFrom(void *widget, BgLayerDesc *desc);
extern int Msg_OpenContainerAndReadHeader(const char *path, int heap, int flags);
extern void func_ov027_020b7d78(void *animSet, Words5 *desc);
extern void func_ov027_020b7e44(void *animSet, u32 key);
extern void *func_ov001_0206468c(int value);
extern void InitializeResourceContainer(void *objectSet, int value);
extern void InitObjManagerAndMark(void *objectSet, Words4 *desc);
extern void func_ov027_020b9098(void *objectSet, u32 key);
extern void func_ov027_020b8fb8(void *objectSet, u32 key, int count);
extern void SetAllElementObjectModes(void *objectSet, int mode);
extern int CreateDefaultObjectSlot(void *objectSet, int resource, int kind, int arg3, int arg4);
extern void func_ov024_020b5848(void *cursor, int value);
extern void *StartBoardScreen(void);

void *CreateBoardScreen(int mode)
{
    Words4 layout = data_ov024_020b7350;
    BgLayerDesc bgDesc;
    Words5 animDesc;
    Words4 objDesc;
    BoardState *state;
    int i;

    state = NNSi_FndGetCurrentRootHeap();
    data_ov024_020b7540.state = state;
    MI_CpuFill8(state, 0, 0x6700);
    MIi_CpuClear32(-1, data_ov024_020b7540.state->cellIds, 0x48);
    MIi_CpuClear32(-1, data_ov024_020b7540.state->nodeIds, 0xa0);
    for (i = 0; i < 6; i++) {
        data_ov024_020b754c[i] = 0;
    }
    data_ov024_020b7540.state->useChannel = (mode == 0x7b);
    if (data_ov024_020b7540.state->useChannel || func_ov001_020645c8(0x3520) || IsFieldFlag13OrSessionFlagSet()) {
        state->showTutorial = 0;
    } else {
        state->showTutorial = 1;
    }
    if (!data_ov024_020b7540.state->useChannel) {
        func_ov001_0207b228(SetupSubScreenBgLayers);
    }
    SetupSubScreenBgLayers();
    if (!data_ov024_020b7540.state->useChannel) {
        SetPanelSessionActive();
    }
    if (data_ov024_020b7540.state->useChannel) {
        bgDesc.layout = &layout;
        bgDesc.count = 4;
        bgDesc.width = 0x20;
        bgDesc.height = 0x20;
        bgDesc.flags = 0;
        data_ov024_020b7540.state->widget = data_ov024_020b7540.state->widgetData;
        InitTileTableFrom(data_ov024_020b7540.state->widget, &bgDesc);
    } else {
        data_ov024_020b7540.state->widget = func_ov001_0207123c();
    }
    data_ov024_020b7540.state->resourceA = Msg_OpenContainerAndReadHeader(sOv024_UiBtlBtluiP2_020b74f4, 0xe, 0);
    data_ov024_020b7540.state->resourceB = Msg_OpenContainerAndReadHeader(sOv024_UiBtlBtlLanguageP2_020b7508, 0xe, 0);
    animDesc = data_ov024_020b7370;
    func_ov027_020b7d78(state->animSet, &animDesc);
    func_ov027_020b7e44(state->animSet, BOARD_VRAM_KEY(data_ov024_020b7540.state->resourceA) | 0x8000000f);
    data_ov024_020b7540.cursor = func_ov001_0206468c(10);
    objDesc = data_ov024_020b7360;
    objDesc.words[0] = BOARD_VRAM_KEY(data_ov024_020b7540.state->resourceA) | 0x80000013;
    InitializeResourceContainer(data_ov024_020b7540.state->objectSet, 0);
    InitObjManagerAndMark(data_ov024_020b7540.state->objectSet, &objDesc);
    func_ov027_020b9098(data_ov024_020b7540.state->objectSet, BOARD_VRAM_KEY(data_ov024_020b7540.state->resourceB) | 0x80000019);
    func_ov027_020b8fb8(data_ov024_020b7540.state->objectSet, BOARD_VRAM_KEY(data_ov024_020b7540.state->resourceA) | 0x80000014, 7);
    SetAllElementObjectModes(data_ov024_020b7540.state->objectSet, 1);
    data_ov024_020b7540.state->markerSlots[0] = CreateDefaultObjectSlot(data_ov024_020b7540.state->objectSet, 0, 0, 0, 0);
    data_ov024_020b7540.state->markerSlots[1] = CreateDefaultObjectSlot(data_ov024_020b7540.state->objectSet, 0, 1, 0, 0);
    if (!data_ov024_020b7540.state->useChannel && IsFieldFlag13OrSessionFlagSet()) {
        if (func_ov001_020645c8(0x3609)) {
            data_ov024_020b7540.state->markerSlots[2] = CreateDefaultObjectSlot(data_ov024_020b7540.state->objectSet, 0, 2, 0, 0);
        }
        if (func_ov001_020645c8(0x360a)) {
            data_ov024_020b7540.state->markerSlots[3] = CreateDefaultObjectSlot(data_ov024_020b7540.state->objectSet, 0, 2, 0, 0);
        }
    }
    for (i = 0; i < 30; i++) {
        data_ov024_020b7540.state->itemSlots[i] = CreateDefaultObjectSlot(data_ov024_020b7540.state->objectSet, 0, 3, 0, 0);
    }
    data_ov024_020b7540.state->cursorSlot = CreateDefaultObjectSlot(data_ov024_020b7540.state->objectSet, 0, 4, 0, 0);
    data_ov024_020b7540.state->targetSlot = CreateDefaultObjectSlot(data_ov024_020b7540.state->objectSet, 0, 5, 0, 0);
    data_ov024_020b7540.state->hintSlot = CreateDefaultObjectSlot(data_ov024_020b7540.state->objectSet, 0, 6, 0, 0);
    data_ov024_020b7540.state->goalSlot = CreateDefaultObjectSlot(data_ov024_020b7540.state->objectSet, 0, 7, 0, 0);
    func_ov024_020b5848(data_ov024_020b7540.cursor, 1);
    data_ov024_020b7540.state->active = 1;
    return StartBoardScreen;
}
