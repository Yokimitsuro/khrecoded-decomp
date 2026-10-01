#include "src/overlays/ov039/RuntimeState.h"

void RuntimeState_SetCondition(int condition) {
    RUNTIME_STATE_TAIL->condition = condition;
}
