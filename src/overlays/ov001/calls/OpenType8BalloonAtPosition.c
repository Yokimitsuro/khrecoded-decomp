#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int func_02028c38(const VecFx32 *worldPos, int *screenX, int *screenY);
extern BOOL func_ov001_0207a504(int balloonType, int style, int arg2, int arg3, int screenX, int screenY,
                                void *message, void *options);

void OpenType8BalloonAtPosition(int style, const VecFx32 *worldPos, void *message, void *options)
{
    int screenX;
    int screenY;

    screenX = 0x7FFFFFFF;
    if (worldPos != NULL) {
        func_02028c38(worldPos, &screenX, &screenY);
        if (screenX < 0 || screenX > 0xFF) {
            screenX = 0x7FFFFFFF;
        }
    }
    func_ov001_0207a504(8, style, 1, 0, screenX, screenY, message, options);
}
