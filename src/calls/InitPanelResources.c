#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x64];
    u32 resourceId;
    u8 pad_68[0x18];
} PanelState;

extern PanelState *data_0205fe24;
extern u32 Archive_LoadFile(u32 fileId, u32 param2, u32 param3, u32 param4);
extern void GetBgDataFromArchive(void *view, u32 resource, int a, int b, int c);
extern void *AllocAndRegisterOrFree(int this_, int arg1, int arg2);
extern u8 sMain_PausePausebgLanguagePbgZ_02055f64[];
extern u8 sMain_PausePauseiconNSCRZ_02055f7c[];
extern u8 sMain_PauseEtciconNSCRZ_02055f94[];

void InitPanelResources(int param1, int param2, u32 param3, u32 param4)
{
    PanelState *panel = data_0205fe24;
    panel->resourceId = Archive_LoadFile((u32)sMain_PausePausebgLanguagePbgZ_02055f64, 0x11, param3, param4);
    GetBgDataFromArchive((u8 *)panel + 0x68, panel->resourceId, 0, 0, 0);
    *(void **)((u8 *)panel + 0x10) = AllocAndRegisterOrFree((int)((u8 *)panel + 0x18), (int)sMain_PausePauseiconNSCRZ_02055f7c, 0x11);
    *(void **)((u8 *)panel + 0xc) = AllocAndRegisterOrFree((int)((u8 *)panel + 0x14), (int)sMain_PauseEtciconNSCRZ_02055f94, 0x11);
}
