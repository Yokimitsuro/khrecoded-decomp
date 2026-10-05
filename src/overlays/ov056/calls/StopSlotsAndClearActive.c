#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x194];
    BOOL isActive;
} BeamEntity;

extern void func_ov021_020aeb8c(BeamEntity *entity);

void StopSlotsAndClearActive(BeamEntity *entity)
{
    func_ov021_020aeb8c(entity);
    entity->isActive = FALSE;
}
