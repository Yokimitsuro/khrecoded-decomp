#include "nitro/types.h"

typedef struct MovieSceneCallbacks {
    void (*open)(int arg);
    void *userData;
    void (*start)(void);
    void (*update)(void);
    BOOL (*isDone)(void);
    void (*close)(void);
    int unk18;
    int unk1c;
    int state;
} MovieSceneCallbacks;

extern void func_ov022_020a7810(int arg);
extern void func_ov022_020a7834(void);
extern void func_ov022_020a7854(void);
extern void func_ov022_020a7878(void);
extern BOOL func_ov022_020a787c(void);

void InitMovieSceneCallbacks(MovieSceneCallbacks *callbacks)
{
    callbacks->open = func_ov022_020a7810;
    callbacks->close = func_ov022_020a7834;
    callbacks->start = func_ov022_020a7854;
    callbacks->update = func_ov022_020a7878;
    callbacks->isDone = func_ov022_020a787c;
    callbacks->userData = NULL;
    callbacks->state = 0;
}
