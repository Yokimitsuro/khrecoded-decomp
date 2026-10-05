#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int func_02028c38(const VecFx32 *worldPos, int *screenX, int *screenY);
extern BOOL OpenMessageWindow_0207a504(int balloonType, int style, int arg2, int arg3, int screenX, int screenY,
                                void *message, void *options);

void OpenType9BalloonAtPosition(const VecFx32 *worldPos, void *message)
{
    int screenX;
    int screenY;

    screenX = 0x7FFFFFFF;
    screenY = 0x7FFFFFFF;
    if (worldPos != NULL) {
        func_02028c38(worldPos, &screenX, &screenY);
        if (screenX < 0 || screenX > 0xFF) {
            screenX = 0x7FFFFFFF;
        }
    }
    OpenMessageWindow_0207a504(9, 0, 0, 0, screenX, screenY, message, NULL);
}
