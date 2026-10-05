#include "nitro/types.h"

typedef struct PanelEntity {
    u8 pad_00[0x94];
    int counterA;
    int counterB;
    int counterC;
} PanelEntity;

void ClearEntityCounters(PanelEntity *entity) {
    entity->counterA = 0;
    entity->counterB = 0;
    entity->counterC = 0;
}
