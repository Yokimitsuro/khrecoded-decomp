#include "nitro/types.h"

typedef struct OverlayActor {
    u8 pad_0000[0x126c];
    int savedMode;
} OverlayActor;

typedef struct FieldState {
    u8 pad_0000[0x27b5];
    u8 savedMode;
} FieldState;

extern OverlayActor *data_ov054_020d3720;
extern FieldState *data_ov001_020a0480;
extern void DestroyActorResources(OverlayActor *actor);
extern void func_ov058_020d7f08(void);

void ShutdownOverlay054(void)
{
    OverlayActor *actor = data_ov054_020d3720;
    int mode;

    if (actor != NULL) {
        mode = actor->savedMode;
        data_ov001_020a0480->savedMode = mode;
        DestroyActorResources(actor);
        func_ov058_020d7f08();
        data_ov054_020d3720 = NULL;
    }
}
