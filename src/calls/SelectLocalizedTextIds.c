#include "nitro/types.h"

typedef struct LocalizedTextIds
{
    u16 unk_00;
    u16 firstId;
    u16 secondId;
    u16 thirdId;
} LocalizedTextIds;

extern LocalizedTextIds data_02055fd4;
extern int func_0202b79c(void);

void SelectLocalizedTextIds(void)
{
    u16 baseId;

    switch (func_0202b79c())
    {
    case 2:
        baseId = 0x3b4;
        data_02055fd4.firstId = baseId;
        data_02055fd4.secondId = baseId + 1;
        data_02055fd4.thirdId = baseId + 2;
        return;
    case 3:
        baseId = 0x3b7;
        data_02055fd4.firstId = baseId;
        data_02055fd4.secondId = baseId + 1;
        data_02055fd4.thirdId = baseId + 2;
        return;
    case 5:
        baseId = 0x3ba;
        data_02055fd4.firstId = baseId;
        data_02055fd4.secondId = baseId + 1;
        data_02055fd4.thirdId = baseId + 2;
        return;
    default:
        baseId = 0x3b1;
        data_02055fd4.firstId = baseId;
        data_02055fd4.secondId = baseId + 1;
        data_02055fd4.thirdId = baseId + 2;
        return;
    }
}
