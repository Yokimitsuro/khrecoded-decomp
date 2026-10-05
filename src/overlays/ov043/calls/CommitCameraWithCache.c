#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    char _0[0x20];
    VecFx32 pos;
} CamActor;

extern u8 *data_ov043_020bd2e0;
extern void camera_commit_projection(CamActor *camera);
extern void func_ov043_020bd0c0(void);

void CommitCameraWithCache(CamActor *camera) {
    *(VecFx32 *)(data_ov043_020bd2e0 + 0xfc) = camera->pos;
    camera_commit_projection(camera);
    func_ov043_020bd0c0();
}
