#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x6690];
    u32 lookup;
} Panel;

extern u16 GetLanguageIndex(void);
extern void WriteGlobalPackedBits(int opcode, int channel, u16 value);
extern u32 func_0202a45c(void *table, int index);
extern int IsSoundStreamActive(int flag);
extern void PrepareAndStartStream(int param1, int param2);

extern u32 data_ov000_020639b8;

void UpdatePanelLookup(Panel *panel)
{
    u16 value = GetLanguageIndex();

    WriteGlobalPackedBits(0x1a02, 3, value);
    panel->lookup = func_0202a45c(&data_ov000_020639b8, 0);
    if (IsSoundStreamActive(0) != 0) {
        return;
    }
    PrepareAndStartStream(0, 0);
}
