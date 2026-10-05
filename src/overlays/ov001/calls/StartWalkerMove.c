#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageWalker {
    u8 pad_000[0x2f0];
    VecFx32 position;
    VecFx32 moveFrom;
    VecFx32 moveTo;
    int moveFrame;
    int moveDuration;
} StageWalker;

void StartWalkerMove(StageWalker *walker, const VecFx32 *target, int frames)
{
    walker->moveFrom = walker->position;
    walker->moveTo = *target;
    walker->moveFrame = 0;
    walker->moveDuration = frames;
    if (frames <= 0) {
        walker->position = *target;
        walker->moveDuration = 0;
    }
}
