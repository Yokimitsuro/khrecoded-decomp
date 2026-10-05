#include "nitro/types.h"

typedef struct {
    u8 pad[4];
    u16 memberIds[3];
} Party;

extern Party *GetSelectionPackedValueBlock(void);
extern u32 func_ov001_0207b3f4(void);
extern u32 func_ov001_0207b610(void);
extern int func_ov025_020b6330(void);

int GetPartySize(void) {
    Party *party = GetSelectionPackedValueBlock();
    int i;
    if (func_ov001_0207b3f4() == 2 && func_ov001_0207b610() != 0) {
        return func_ov025_020b6330();
    }
    for (i = 0; i < 3; i++) {
        if (party->memberIds[i] == 0xffff) {
            break;
        }
    }
    return i + 1;
}
