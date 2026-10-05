#include "nitro/types.h"

extern u8 sOv052_Root_020d2160[];
extern u8 sOv052_Bip01_020d2168[];
extern u8 sOv052_WeaponTg00_020d2170[];
extern u8 sOv052_Bip01LHand_020d217c[];

void *gWeaponAttachmentBoneNames[4] = {
    sOv052_WeaponTg00_020d2170,
    sOv052_Bip01LHand_020d217c,
    sOv052_Root_020d2160,
    sOv052_Bip01_020d2168,
};
