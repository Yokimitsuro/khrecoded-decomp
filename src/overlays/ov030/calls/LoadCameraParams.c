#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraParams {
    u32 unk_00;
    VecFx32 origin;
    fx32 unk_10;
    fx32 unk_14;
    fx32 unk_18;
    u32 unk_1C;
    fx32 unk_20;
    fx32 unk_24;
    u8 pad_28[4];
    u8 body[1];
} CameraParams;

typedef struct MoviePlayerCtx {
    u8 pad_00[0x30];
    CameraParams *cameraParams;
    u8 *cameraBody;
    u8 pad_38[0x18];
    s32 unk_50;
} MoviePlayerCtx;

extern MoviePlayerCtx *data_ov030_020bd020;
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern u32 func_ov001_020636e4(void);
extern int findSharedResourceByName(unsigned char *table, void *name);
extern CameraParams *Archive_LoadFile(u32 fileId, u32 param2, u32 param3, u32 param4);
extern void func_ov030_020bb2ec(VecFx32 *origin, fx32 a, fx32 b, fx32 c, s32 flag, fx32 d);
extern void SetCameraMode(u32 flags);
extern void func_ov042_020bd600(fx32 value);
extern void SetSceneLock(u8 value);

void LoadCameraParams(void *name)
{
    u32 archiveHandle;
    int entryIndex;
    u32 archiveBits;
    CameraParams *params;

    if (data_ov030_020bd020->cameraParams != NULL) {
        NNSi_FndFreeFromDefaultHeap(data_ov030_020bd020->cameraParams);
    }
    archiveHandle = func_ov001_020636e4();
    entryIndex = findSharedResourceByName((unsigned char *)func_ov001_020636e4(), name);
    archiveBits = ((archiveHandle + 0x8000) & 0xfffffc) << 7 | 0x80000000;
    data_ov030_020bd020->cameraParams =
        Archive_LoadFile((entryIndex & 0x1ff) | archiveBits, 2, 0xfffffc, archiveBits);
    data_ov030_020bd020->cameraBody = data_ov030_020bd020->cameraParams->body;
    params = data_ov030_020bd020->cameraParams;
    func_ov030_020bb2ec(&params->origin, params->unk_10, params->unk_14, params->unk_18, 0,
                        params->unk_20);
    SetCameraMode(data_ov030_020bd020->cameraParams->unk_1C);
    func_ov042_020bd600(data_ov030_020bd020->cameraParams->unk_24);
    data_ov030_020bd020->unk_50 = -1;
    SetSceneLock(1);
}
