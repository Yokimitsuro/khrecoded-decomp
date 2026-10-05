#include "nitro/types.h"

typedef struct MovieScene {
    u8 pad_000[0x10b];
    u8 visible;
} MovieScene;

extern MovieScene *data_ov035_020bc504;
extern void func_01ffb12c(MovieScene *node);

void DrawMovieSceneIfVisible(void)
{
    if (data_ov035_020bc504->visible) {
        func_01ffb12c(data_ov035_020bc504);
    }
}