#include "nitro/types.h"

typedef struct PanelResources {
    u8 pad_00[0x30];
    u8 fontA[0xc];
    u8 fontB[0x118 - 0x3c];
    u8 messagesA[0xc];
    u8 messagesB[0xc];
} PanelResources;

typedef struct PanelPaths {
    const char *fontB;
    const char *fontA;
    const char *messagesB;
    const char *messagesA;
} PanelPaths;

extern PanelResources *data_ov002_0206c460;
extern PanelPaths gPanelResourcePaths;
extern void ResetDisplayHardware(void);
extern int func_0200146c(void *font, const char *path);
extern void LoadPackedFileView(void *messages, const char *path, int flags);
extern void func_ov002_02062254(void);
extern void func_ov002_02062368(void);

void ReloadPanelResources(void)
{
    ResetDisplayHardware();
    func_0200146c(data_ov002_0206c460->fontA, gPanelResourcePaths.fontA);
    func_0200146c(data_ov002_0206c460->fontB, gPanelResourcePaths.fontB);
    LoadPackedFileView(data_ov002_0206c460->messagesA, gPanelResourcePaths.messagesA, 1);
    LoadPackedFileView(data_ov002_0206c460->messagesB, gPanelResourcePaths.messagesB, 1);
    func_ov002_02062254();
    func_ov002_02062368();
}
