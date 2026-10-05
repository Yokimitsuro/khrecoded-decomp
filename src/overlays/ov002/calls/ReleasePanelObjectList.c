#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x10];
    u8 flags_b0 : 4;
    u8 hasListA : 1;
    u8 hasListB : 1;
    u8 flags_b6 : 2;
    u8 pad_11[0xb0 - 0x11];
    u8 listA[0xe4 - 0xb0];
    u8 listB[4];
} PanelState;

extern PanelState *data_ov002_0206c460;
extern void DestroyFndObjectList(void *list);

void ReleasePanelObjectList(int which)
{
    if (which == 0) {
        if (data_ov002_0206c460->hasListA) {
            DestroyFndObjectList(data_ov002_0206c460->listA);
        }
        data_ov002_0206c460->hasListA = 0;
    } else {
        if (data_ov002_0206c460->hasListB) {
            DestroyFndObjectList(data_ov002_0206c460->listB);
        }
        data_ov002_0206c460->hasListB = 0;
    }
}
