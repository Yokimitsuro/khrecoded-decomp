#include "nitro/types.h"

typedef struct {
    u8 data[0x134];
} SceneModel;

typedef struct {
    u8 pad_000[0x2a8];
    SceneModel models[3];
} SceneModelBlock;

extern u8 data_ov058_020d8bb8[];
extern u8 data_ov058_020d9088[];
extern SceneModelBlock data_ov058_020d8a44;

extern void func_ov058_020d7740(void *node);
extern void func_ov058_020d79a0(void *node);
extern void ApplyModelPolygonId(SceneModel *object, int polygonBase);

void DrawSceneModels(void)
{
    SceneModelBlock *block = &data_ov058_020d8a44;
    int i;

    func_ov058_020d7740(data_ov058_020d8bb8);
    func_ov058_020d79a0(data_ov058_020d9088);
    for (i = 0; i < 3; i++) {
        ApplyModelPolygonId(&block->models[i], i);
    }
}
