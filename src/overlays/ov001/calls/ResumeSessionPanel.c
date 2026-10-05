#include "nitro/types.h"

typedef struct SessionPanel {
    u8 pad_000[0xc];
    u8 widget[0x98];
    s8 state;
} SessionPanel;

typedef struct Session {
    u8 pad_0000[0x2800];
    SessionPanel panel;
} Session;

extern Session *data_ov001_020a0480;
extern void func_ov037_020bacb8(void *widget);

void ResumeSessionPanel(void)
{
    SessionPanel *panel = &data_ov001_020a0480->panel;

    if (panel->state == 3) {
        panel->state = 2;
    }
    func_ov037_020bacb8(panel->widget);
}
