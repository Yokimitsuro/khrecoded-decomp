#include "nitro/types.h"

typedef struct {
    u16 angles[3];
} SlotAngleTable;

typedef struct {
    u8 pad_00[0x20];
    u16 baseAngle;
} SceneAngleState;

extern const SlotAngleTable data_ov058_020d89b4;
extern SceneAngleState data_ov058_020d8a44;

u16 GetSceneSlotAngle(int slot)
{
    SlotAngleTable table = data_ov058_020d89b4;

    return data_ov058_020d8a44.baseAngle + table.angles[slot] + 0x8000;
}
