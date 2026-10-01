#include "src/overlays/ov039/RuntimeState.h"

void RuntimeState_SetFlags(int flags) {
    RUNTIME_STATE_TAIL->flags = flags;
}
