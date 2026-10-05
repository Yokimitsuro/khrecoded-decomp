#include "nitro/types.h"

typedef struct {
    int values[3];
} IdTriple;

typedef struct {
    u8 pad_000[0xb64];
    u8 labelTable[0x54];
    int variant;
} PanelScene;

extern const IdTriple data_ov087_020c7ca8;
extern const IdTriple data_ov087_020c7ccc;
extern void *func_ov027_020ba2c8(void *table, int index);
extern void func_ov087_020c4880(PanelScene *scene, const u16 *text);
extern void func_ov001_020645dc(int flagId);

void ShowVariantMessageAndSetFlag(PanelScene *scene)
{
    IdTriple messageIds = data_ov087_020c7ca8;
    IdTriple flagIds = data_ov087_020c7ccc;

    func_ov087_020c4880(scene, func_ov027_020ba2c8(scene->labelTable, messageIds.values[scene->variant]));
    func_ov001_020645dc(flagIds.values[scene->variant] + 0xf50);
}
