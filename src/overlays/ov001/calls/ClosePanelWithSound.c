#include "nitro/types.h"

typedef struct Panel Panel;

struct Panel {
    u8 pad_00[0x6c];
    void (*onClose)(Panel *panel);
};

extern void func_ov001_0208273c(Panel *panel, int state);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

int ClosePanelWithSound(int unused0, int unused1, int unused2, Panel *panel)
{
    if (panel->onClose != NULL) {
        panel->onClose(panel);
    }
    func_ov001_0208273c(panel, 2);
    PlaySoundEffect(0, 0x3a);
    return 0;
}
