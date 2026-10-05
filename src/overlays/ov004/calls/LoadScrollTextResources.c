#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    void *messageData;
    u8 pad_10[0x23a9c - 0x10];
    void *mainFontFile;
    u8 pad_23aa0[0x23aa8 - 0x23aa0];
    void *subFontFile;
    u8 pad_23aac[0x23ac4 - 0x23aac];
    u32 unk_23ac4_0 : 1;
    u32 loading : 1;
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals data_ov004_020645a0;
extern char sOv004_SfSfP2_02064544[];
extern char sOv004_SfSffont10Nftr_02064550[];
extern char sOv004_SfSffont8Nftr_02064564[];

extern void SetBrightnessAndSyncMain(int value);
extern void SetSecondaryBrightness(int value);
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern void *func_0202c378(const char *path, u32 mode);
extern void InitTitleDisplay(void);
extern void func_ov004_0206366c(void);
extern int func_0202c44c(void);
extern void func_ov004_02063598(void);
extern void InitScrollTextLayers(void);
extern void LoadScrollTextEntryTable(void);
extern u32 TaskManager_SetEnabled(u32 argument0);
extern void G2x_SetBlendBrightness_(u32 regAddr, int plane, int brightness);
extern void ResetScrollTextScript(void);
extern void RunScrollTextFrame(void);

void *LoadScrollTextResources(void)
{
    SetBrightnessAndSyncMain(-16);
    SetSecondaryBrightness(-16);
    data_ov004_020645a0.work->messageData = Msg_OpenContainerAndReadHeader(sOv004_SfSfP2_02064544, 0xe, FALSE);
    data_ov004_020645a0.work->mainFontFile = func_0202c378(sOv004_SfSffont10Nftr_02064550, 0xe);
    data_ov004_020645a0.work->subFontFile = func_0202c378(sOv004_SfSffont8Nftr_02064564, 0xe);
    InitTitleDisplay();
    func_ov004_0206366c();
    func_0202c44c();
    func_ov004_02063598();
    InitScrollTextLayers();
    LoadScrollTextEntryTable();
    TaskManager_SetEnabled(0);
    G2x_SetBlendBrightness_(0x04000050, 4, -16);
    G2x_SetBlendBrightness_(0x04001050, 4, -16);
    SetBrightnessAndSyncMain(0);
    SetSecondaryBrightness(0);
    ResetScrollTextScript();
    data_ov004_020645a0.work->loading = 0;
    return RunScrollTextFrame;
}
