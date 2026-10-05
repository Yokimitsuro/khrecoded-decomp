#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScreenPoint {
    fx32 x;
    fx32 y;
} ScreenPoint;

typedef struct SpriteSlot {
    u8 pad_00[0x10];
    ScreenPoint position;
    u8 pad_18[0xc];
    u8 isVisible;
    u8 pad_25[0xb];
} SpriteSlot;

typedef struct ScreenManager {
    u8 pad_00[0x30];
    SpriteSlot sprite;
    u32 vramOffset;
} ScreenManager;

typedef struct VariantTable {
    s8 entries[10];
} VariantTable;

extern ScreenManager *data_ov001_020a04a0;
extern const ScreenPoint data_ov001_0209da94;
extern const VariantTable data_ov001_0209da9c;
extern void LoadSlotTextureFile(SpriteSlot *slot, u32 resourceKey);

void LoadCenteredScreenSprite(int variant)
{
    VariantTable table = data_ov001_0209da9c;

    LoadSlotTextureFile(&data_ov001_020a04a0->sprite,
                        0x80000000 | ((data_ov001_020a04a0->vramOffset + 0x8000) & 0xfffffc) << 7 |
                            (table.entries[variant] & 0x1ff));
    data_ov001_020a04a0->sprite.isVisible = 1;
    data_ov001_020a04a0->sprite.position = data_ov001_0209da94;
}
