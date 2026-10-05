#include "nitro/types.h"

extern u8 sOv059_AbPZ_020cff00[];
extern u8 sOv059_EtcPZ_020cff08[];
extern u8 sOv059_ShootingPZ_020cff1c[];

void *gBattleEffectPathParts[3] = {
    sOv059_ShootingPZ_020cff1c,
    sOv059_AbPZ_020cff00,
    sOv059_EtcPZ_020cff08,
};
