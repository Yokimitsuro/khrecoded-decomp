#include "nitro/types.h"

typedef struct {
    u8 data[0x134];
} SceneModel;

typedef struct {
    u8 enabled;
    u8 pad_001[0x30 - 0x1];
    s32 phase;
    s32 counter;
    void *buffer;
    u8 pad_03c[0x154 - 0x3c];
    s32 (*maskCallback)(s32 value);
    u8 pad_158[0x2a8 - 0x158];
    SceneModel models[3];
    u8 pad_644[0x798 - 0x644];
    u8 cameraPath[4];
} SceneModelBlock;

extern SceneModelBlock data_ov058_020d8a44;
extern u8 data_ov058_020d8a80[];
extern const char sOv058_BaChSoTMPZ_020d8a00[];
extern const char sOv058_BaEfFnTrP2_020d8a14[];
extern const char sOv058_CmAR_020d8a24[];
extern SceneModel data_ov058_020d8bb8;
extern SceneModel data_ov058_020d9088;

extern void InitAnimatedModel(void *model, const char *source, int slot);
extern s32 ToBoolMask(s32 value);
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern void LoadArchiveEffectSlot(SceneModel *slot, u32 fileIndex);
extern void CameraPath_Load(void *path, const char *file);
extern void LoadManagerSpriteSlots(void);

void LoadSceneModelResources(void)
{
    SceneModelBlock *block = &data_ov058_020d8a44;
    int i = 0;

    block->enabled = 0;
    block->phase = 0;
    block->counter = 0;
    InitAnimatedModel(data_ov058_020d8a80, sOv058_BaChSoTMPZ_020d8a00, 0);
    block->maskCallback = ToBoolMask;
    block->buffer = Msg_OpenContainerAndReadHeader(sOv058_BaEfFnTrP2_020d8a14, 6, FALSE);
    LoadArchiveEffectSlot(&data_ov058_020d8bb8, 2);
    LoadArchiveEffectSlot(&data_ov058_020d9088, 4);
    for (; i < 3; i++) {
        LoadArchiveEffectSlot(&block->models[i], 3);
    }
    CameraPath_Load(block->cameraPath, sOv058_CmAR_020d8a24);
    LoadManagerSpriteSlots();
}
