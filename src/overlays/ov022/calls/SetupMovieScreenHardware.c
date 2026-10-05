#include "nitro/types.h"

extern void movie_video_hardware_setup(void);
extern void SetupSubScreenForMovie(void);

void SetupMovieScreenHardware(int useMainScreen)
{
    if (useMainScreen != 0) {
        movie_video_hardware_setup();
        return;
    }
    SetupSubScreenForMovie();
}
