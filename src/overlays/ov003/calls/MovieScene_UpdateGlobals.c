#include "nitro/types.h"

typedef struct MovieScene {
    u8 pad_000[0x8b9];
    u8 queuePending;
} MovieScene;

extern MovieScene *data_ov003_020658c0;
extern void NNS_GfdDoVramTransfer(void);
extern void func_ov003_02063a20(MovieScene *scene);
extern void SoundMgr_Update(void);

void MovieScene_UpdateGlobals(void)
{
    MovieScene *scene = data_ov003_020658c0;

    if (scene == NULL) {
        return;
    }
    if (scene->queuePending) {
        NNS_GfdDoVramTransfer();
        data_ov003_020658c0->queuePending = 0;
    }
    func_ov003_02063a20(scene);
    SoundMgr_Update();
}
