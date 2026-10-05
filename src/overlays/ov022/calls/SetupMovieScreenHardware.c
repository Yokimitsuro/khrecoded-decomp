#include "nitro/types.h"

extern void func_ov022_020a7b5c(void);
extern void func_ov022_020a7c78(void);

void SetupMovieScreenHardware(int useMainScreen)
{
    if (useMainScreen != 0) {
        func_ov022_020a7b5c();
        return;
    }
    func_ov022_020a7c78();
}
