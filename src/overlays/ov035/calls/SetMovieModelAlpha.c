#include "nitro/types.h"

typedef struct MovieScene {
    u8 pad_000[0x78];
    void *model;
    u8 pad_07c[0x8a];
    s16 modelIndex;
} MovieScene;

extern MovieScene *data_ov035_020bc504;
extern s8 data_ov035_020bc40c[];
extern void NNS_G3dMdlSetMdlAlphaAll(void *model, int alpha);

void SetMovieModelAlpha(int level)
{
    if (data_ov035_020bc504->modelIndex >= 0) {
        if (level == 0xff) {
            level = 0;
        }
        NNS_G3dMdlSetMdlAlphaAll(data_ov035_020bc504->model, data_ov035_020bc40c[level]);
    }
}