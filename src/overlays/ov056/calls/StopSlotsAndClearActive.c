#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x194];
    BOOL isActive;
} BeamEntity;

extern void ResetCountsAndSlots(BeamEntity *entity);

void StopSlotsAndClearActive(BeamEntity *entity)
{
    ResetCountsAndSlots(entity);
    entity->isActive = FALSE;
}
