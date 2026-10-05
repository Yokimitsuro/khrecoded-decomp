#include "nitro/types.h"

typedef struct PendingState {
    u8 pad_00[0x10];
    int pending;
    int index;
} PendingState;

extern PendingState data_ov021_020b5640;
extern int data_ov021_020b5644[];

void SetPendingFromTable(int index)
{
    if (data_ov021_020b5640.pending == 0) {
        data_ov021_020b5640.pending = data_ov021_020b5644[index];
        data_ov021_020b5640.index = index;
    }
}
