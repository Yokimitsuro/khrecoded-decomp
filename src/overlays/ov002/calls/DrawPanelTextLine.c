#include "nitro/types.h"

typedef struct PanelTextFlags {
    u8 firstShown : 1;
    u8 rest : 7;
} PanelTextFlags;

typedef struct PanelState {
    u8 pad_00[0x11];
    union {
        PanelTextFlags bits;
        u8 raw;
    } textFlags;
} PanelState;

extern PanelState *data_ov002_0206c460;
extern void func_0200177c(void *entry, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8);

void DrawPanelTextLine(int selectSecond, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8) {
    void *entry;

    if (!selectSecond) {
        entry = (u8 *)data_ov002_0206c460 + 0xb0;
        data_ov002_0206c460->textFlags.bits.firstShown = 1;
    } else {
        entry = (u8 *)data_ov002_0206c460 + 0xe4;
        data_ov002_0206c460->textFlags.raw |= 2;
    }
    func_0200177c(entry, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}
