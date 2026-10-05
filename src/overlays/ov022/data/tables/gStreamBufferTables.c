#include "nitro/types.h"

extern u8 data_ov022_020b7c90[];
extern u8 data_ov022_020b7c30[];
extern u8 data_ov022_020b7c50[];
extern u8 data_ov022_020b7c78[];
extern u8 data_ov022_020b7c40[];
extern u8 data_ov022_020b7c64[];

void *gStreamBufferTables[6] = {
    data_ov022_020b7c90,
    data_ov022_020b7c30,
    data_ov022_020b7c50,
    data_ov022_020b7c78,
    data_ov022_020b7c40,
    data_ov022_020b7c64,
};
