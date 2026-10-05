#include "nitro/types.h"

typedef struct {
    u8 opaque[0x34];
} TextLayer;

typedef struct {
    u8 data[0x6434];
} SpriteManager;

typedef struct {
    u8 opaque[8];
} FontResource;

typedef struct {
    u8 pad_00[4];
    void *unk_04;
    void *unk_08;
    u8 pad_0c[0x1c - 0xc];
    TextLayer textLayer;
    TextLayer markerLayer;
    u8 pad_84[0x10940 - 0x84];
} ScrollScreen;

typedef struct {
    u8 pad_00[0xc];
    void *messageData;
    void *unk_10;
    ScrollScreen screens[2];
    u8 pad_21294[0x23a94 - 0x21294];
    FontResource mainFont;
    u8 pad_23a9c[4];
    FontResource subFont;
    u8 pad_23aa8[0x23ac8 - 0x23aa8];
    s32 skipSceneChange;
    u8 pad_23acc[0x23ad4 - 0x23acc];
    SpriteManager managers[2];
    void *unk_3033c;
    void *unk_30340;
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

typedef struct {
    s16 sceneId;
    s16 entryId;
    u8 kind;
    u8 pad_05[7];
} SceneArgs;

extern ScrollTextGlobals data_ov004_020645a0;
extern SceneArgs data_02060850;

extern int ZeroHalfThenFree(void *data);
extern int Obj_Release(void *object);
extern BOOL DestroyFndObjectList(TextLayer *layer);
extern BOOL FreeResourceBufferAndProbeHeap(FontResource *resource);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void func_01ff88c4(void *dst, u32 value, u32 size);
extern void SetPendingScene(s32 pendId, s32 pendArg);

void ReleaseScrollTextWork(void)
{
    ZeroHalfThenFree(data_ov004_020645a0.work->messageData);
    Obj_Release(&data_ov004_020645a0.work->managers[0]);
    Obj_Release(&data_ov004_020645a0.work->managers[1]);
    DestroyFndObjectList(&data_ov004_020645a0.work->screens[0].textLayer);
    DestroyFndObjectList(&data_ov004_020645a0.work->screens[0].markerLayer);
    DestroyFndObjectList(&data_ov004_020645a0.work->screens[1].textLayer);
    DestroyFndObjectList(&data_ov004_020645a0.work->screens[1].markerLayer);
    FreeResourceBufferAndProbeHeap(&data_ov004_020645a0.work->mainFont);
    FreeResourceBufferAndProbeHeap(&data_ov004_020645a0.work->subFont);
    NNSi_FndFreeFromDefaultHeap(data_ov004_020645a0.work->unk_30340);
    NNSi_FndFreeFromDefaultHeap(data_ov004_020645a0.work->unk_3033c);
    NNSi_FndFreeFromDefaultHeap(data_ov004_020645a0.work->unk_10);
    NNSi_FndFreeFromDefaultHeap(data_ov004_020645a0.work->screens[0].unk_04);
    NNSi_FndFreeFromDefaultHeap(data_ov004_020645a0.work->screens[1].unk_04);
    NNSi_FndFreeFromDefaultHeap(data_ov004_020645a0.work->screens[0].unk_08);
    NNSi_FndFreeFromDefaultHeap(data_ov004_020645a0.work->screens[1].unk_08);
    if (data_ov004_020645a0.work->skipSceneChange == 0) {
        func_01ff88c4(&data_02060850, 0, sizeof(SceneArgs));
        data_02060850.sceneId = 899;
        data_02060850.entryId = -1;
        data_02060850.kind = 4;
        SetPendingScene(2, 0);
    }
    data_ov004_020645a0.work = NULL;
}
