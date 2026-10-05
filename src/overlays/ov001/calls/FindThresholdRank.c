#include "nitro/types.h"

extern u32 data_ov001_0209e13c[][3];

int FindThresholdRank(int row, u32 value)
{
    int result = 3;
    int rank;

    for (rank = 0; rank < 3; rank++) {
        if (value >= data_ov001_0209e13c[row][rank]) {
            result = rank;
            break;
        }
    }
    return result;
}
