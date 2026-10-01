#include "src/overlays/ov039/RuntimeState.h"

void RuntimeState_SetObjectId(int objectId) {
    RUNTIME_STATE_TAIL->objectId = objectId;
}
