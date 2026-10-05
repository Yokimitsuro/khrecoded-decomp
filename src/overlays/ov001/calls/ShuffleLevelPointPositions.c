#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct LevelPoint {
    u8 pad_00[8];
    VecFx32 position;
    u8 pad_14[0x1c];
} LevelPoint;

typedef struct LevelTableFile {
    u8 pad_00[8];
    LevelPoint *points;
} LevelTableFile;

typedef struct LevelTableHolder {
    LevelTableFile *file;
} LevelTableHolder;

extern LevelTableHolder *data_ov001_020a0490;
extern u32 func_0202a9e4(u16 range);

void ShuffleLevelPointPositions(int count, const int *indices)
{
    LevelTableHolder *holder = data_ov001_020a0490;
    VecFx32 positions[128];
    int order[128];
    int pass;
    int i;
    int j;
    int swap;

    for (i = 0; i < count; i++) {
        positions[i] = holder->file->points[indices[i]].position;
        order[i] = i;
    }
    for (pass = 0; pass < 4; pass++) {
        for (i = 0; i < count; i++) {
            j = func_0202a9e4(count);
            if (j != i) {
                swap = order[i];
                order[i] = order[j];
                order[j] = swap;
            }
        }
    }
    for (i = 0; i < count; i++) {
        holder->file->points[indices[i]].position = positions[order[i]];
    }
}
