#include "nitro/types.h"

typedef struct SessionPanel {
    u8 pad_000[0xc];
    u8 widget[0xa0];
    int counter;
    int active;
    char name[0x80];
    int pending;
} SessionPanel;

typedef struct Session {
    u8 pad_0000[0x2800];
    SessionPanel panel;
} Session;

extern Session *data_ov001_020a0480;
extern char sOv001_M_0209e6f8[];
extern void InitMovieSceneCallbacks(void *widget);
extern int OS_SPrintf(char *dst, const char *fmt, ...);

void ResetSessionPanel(void)
{
    SessionPanel *panel = &data_ov001_020a0480->panel;

    InitMovieSceneCallbacks(panel->widget);
    panel->counter = 0;
    panel->active = 1;
    panel->pending = 0;
    OS_SPrintf(panel->name, sOv001_M_0209e6f8);
}
