#include "nitro/types.h"

extern int func_ov003_02064c10(int stream);

/* Resets the subtitle cursor and clamps the step. */
int ClampMovieSubtitleStep(int stream, int minStep)
{
    int step;

    step = func_ov003_02064c10(stream);
    *(int *)(stream + 0x58) = 0;
    if (step <= minStep) {
        step = minStep;
    }
    return step;
}
