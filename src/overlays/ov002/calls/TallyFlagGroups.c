#include "nitro/types.h"

extern u8 *func_ov002_02066fb0(void);
extern s8 data_ov002_0206ad8c[];
extern u16 data_ov002_0206adb4[];

void TallyFlagGroups(u16 *totals)
{
    u8 *flags = func_ov002_02066fb0();
    int bitCount = 0;
    int groupSum = 0;
    int groupIndex = 0;
    int boundIndex = 1;
    int byteIndex;
    int bit;
    int i;
    u8 value;

    for (i = 0; i < 4; i++) {
        totals[i] = 0;
    }
    for (byteIndex = 0; byteIndex < 0x67; byteIndex++) {
        value = flags[byteIndex];
        for (bit = 0; bit < 8; bit++) {
            bitCount++;
            if (value & (1 << bit)) {
                groupSum++;
            }
            if (bitCount >= data_ov002_0206adb4[boundIndex]) {
                totals[data_ov002_0206ad8c[groupIndex]] += (u16)groupSum;
                groupSum = 0;
                groupIndex++;
                boundIndex++;
                if (groupIndex == 0x12) {
                    groupIndex++;
                }
                if (boundIndex == 0x12) {
                    boundIndex++;
                }
            }
        }
    }
}
