#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageWalker {
    u8 pad_000[0x28a];
    u16 moveMode : 2;
    u16 otherFlags : 14;
    u8 pad_28C[0x10];
    int moveFrames;
    int moveExtra;
    u8 pad_2A4[0x1c];
    VecFx32 position;
    VecFx32 targetPosition;
    VecFx32 followPosition;
} StageWalker;

void BeginWalkerMove(StageWalker *walker, const VecFx32 *target, int frames, int extra)
{
    if (frames < 0) {
        walker->position = *target;
        walker->targetPosition = *target;
        walker->moveFrames = 0;
        walker->moveExtra = 0;
        return;
    }
    walker->targetPosition = *target;
    walker->moveFrames = frames;
    walker->moveExtra = extra;
    if (walker->moveMode == 1) {
        walker->followPosition = walker->targetPosition;
    }
}
