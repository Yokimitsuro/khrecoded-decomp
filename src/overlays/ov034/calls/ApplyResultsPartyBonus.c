#include "nitro/types.h"

typedef struct ResultsParams {
    u8 pad_00[0xc];
    u16 bonusCount;
    u8 pad_0e[4];
    s16 bonusPoints;
    u8 pad_14[0x12];
    s8 stageKind;
    u8 pad_27[0xa];
    s8 memberIds[6];
    u8 pad_37[0x1f];
    s8 memberLevels[6];
    u8 pad_5c[0x12];
    s8 bonusMask;
} ResultsParams;

typedef struct PartyBonusEntry {
    u8 values[2][3];
} PartyBonusEntry;

extern PartyBonusEntry data_ov034_020be980[];

void ApplyResultsPartyBonus(ResultsParams *params)
{
    int total;
    int slot;
    int j;
    int id;

    if (params->stageKind == 0x1f) {
        total = 0;
        for (slot = 0; slot < 6; slot++) {
            id = params->memberIds[slot];
            if (id >= 0) {
                for (j = 0; j < 3; j++) {
                    total += data_ov034_020be980[id].values[params->memberLevels[slot] ? 1 : 0][j];
                }
            }
        }
        params->bonusCount = total * params->bonusCount / 100;
    }
    if (params->bonusPoints == 0) {
        total = 0;
        for (slot = 0; slot < 6; slot++) {
            if (params->memberIds[slot] >= 0 && params->memberLevels[slot] > 0) {
                for (j = 0; j < 3; j++) {
                    if ((1 << j) & params->bonusMask) {
                        total += data_ov034_020be980[params->memberIds[slot]].values[1][j];
                    }
                }
            }
        }
        params->bonusPoints = total;
    }
}
