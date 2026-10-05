#include "nitro/types.h"

extern u8 data_ov015_0207a1fc[];
extern u8 data_ov015_0207a208[];
extern u8 data_ov015_0207a22c[];
extern u8 data_ov015_0207a240[];
extern u8 data_ov015_0207a258[];
extern u8 data_ov015_0207a274[];
extern u8 data_ov015_0207a294[];
extern u8 gWirelessResourceTableC[];
extern u8 gWirelessResourceTableB[];
extern u8 gWirelessResourceTableA[];

void *gWirelessModeDataTables[10] = {
    NULL,
    NULL,
    NULL,
    data_ov015_0207a1fc,
    data_ov015_0207a208,
    data_ov015_0207a22c,
    data_ov015_0207a240,
    data_ov015_0207a258,
    data_ov015_0207a274,
    data_ov015_0207a294,
};

void *gWirelessResourceTables[7] = {
    NULL,
    gWirelessResourceTableC,
    gWirelessResourceTableC,
    gWirelessResourceTableC,
    gWirelessResourceTableC,
    gWirelessResourceTableB,
    gWirelessResourceTableA,
};
