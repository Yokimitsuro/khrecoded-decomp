#include "nitro/types.h"

typedef struct TimerNode {
    u8 unknown_00[8];
    int duration;
    u8 unknown_0c[4];
    int elapsed;
} TimerNode;

void SetTimerDuration(TimerNode *node, int duration) {
    node->duration = duration;
    node->elapsed = 0;
}
