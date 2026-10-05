#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0x220];
    VecFx32 currentPositions[3];
    u16 currentAngles[3];
    u8 pad_24a[0x2748 - 0x24a];
    VecFx32 savedPositions[3];
    u16 savedAngles[3];
} Session;

extern Session *data_ov001_020a0480;

void SaveCurrentSpawnPoint(int index) {
    Session *session = data_ov001_020a0480;
    session->savedPositions[index] = session->currentPositions[index];
    session->savedAngles[index] = session->currentAngles[index];
}
