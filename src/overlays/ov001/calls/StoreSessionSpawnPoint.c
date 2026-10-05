#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0x2748];
    VecFx32 positions[3];
    u16 angles[3];
    u8 pad_2772[0x27b6 - 0x2772];
    u8 locked : 1;
} Session;

extern Session *data_ov001_020a0480;

void StoreSessionSpawnPoint(int index, const VecFx32 *position, u16 angle) {
    Session *session = data_ov001_020a0480;
    if (!session->locked) {
        session->positions[index] = *position;
        session->angles[index] = angle;
    }
}
