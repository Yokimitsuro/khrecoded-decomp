#include "nitro/types.h"

typedef struct MovieContext {
    u8 pad_00[0x2c];
    s16 baseLimit;
} MovieContext;

extern MovieContext *data_ov035_020bc500;

int GetMovieCounterLimit(int which)
{
    switch (which) {
    case 0:
        return data_ov035_020bc500->baseLimit;
    case 1:
        return (data_ov035_020bc500->baseLimit * 130 + 50) / 100;
    case 2:
        return (data_ov035_020bc500->baseLimit * 115 + 50) / 100;
    }
    return -1;
}