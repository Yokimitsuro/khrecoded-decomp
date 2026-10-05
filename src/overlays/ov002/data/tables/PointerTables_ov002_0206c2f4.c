#include "nitro/types.h"

extern void func_ov002_02064394(void); /* PXI_Init */
extern void ClosePanelAndQueueScene(void); /* ClosePanelAndQueueScene */
extern void func_ov002_02062dd8(void);
extern void func_ov002_02062ddc(void);
extern void func_ov002_02062de0(void); /* LoadPanelOverlay14 */
extern void func_ov002_02062dfc(void);
extern void func_ov002_02062e18(void); /* UnloadPanelOverlay14 */
extern void func_ov014_0206cfa0(void); /* UpdatePanelBanner */
extern void func_ov002_02062e48(void); /* LoadPanelOverlay13 */
extern void PollPanelOverlay13(void); /* PollPanelOverlay13 */
extern void func_ov002_02062e98(void); /* UnloadPanelOverlay13 */
extern void func_ov013_0206c9d4(void);
extern void func_ov002_02062f60(void);
extern void func_ov002_02062f80(void);
extern void func_ov002_02062f84(void);
extern void func_ov002_02062ec8(void);
extern void func_ov002_02062ecc(void); /* OSi_IrqDma0 */
extern void func_ov002_02062edc(void);
extern void func_ov002_02062ee0(void); /* LoadPanelOverlay15 */
extern void PollPanelOverlay15(void); /* PollPanelOverlay15 */
extern void func_ov002_02062f30(void); /* UnloadPanelOverlay15 */
extern void func_ov015_0206c5dc(void);
extern void func_ov002_02062d94(void); /* PXI_Init */

void (*gPanelSceneStateHandlers[25])(void) = {
    func_ov002_02064394, /* PXI_Init */
    ClosePanelAndQueueScene, /* ClosePanelAndQueueScene */
    func_ov002_02062dd8,
    func_ov002_02062ddc,
    NULL,
    func_ov002_02062de0, /* LoadPanelOverlay14 */
    func_ov002_02062dfc,
    func_ov002_02062e18, /* UnloadPanelOverlay14 */
    func_ov014_0206cfa0, /* UpdatePanelBanner */
    func_ov002_02062e48, /* LoadPanelOverlay13 */
    PollPanelOverlay13, /* PollPanelOverlay13 */
    func_ov002_02062e98, /* UnloadPanelOverlay13 */
    func_ov013_0206c9d4,
    func_ov002_02062f60,
    func_ov002_02062f80,
    func_ov002_02062f84,
    NULL,
    func_ov002_02062ec8,
    func_ov002_02062ecc, /* OSi_IrqDma0 */
    func_ov002_02062edc,
    NULL,
    func_ov002_02062ee0, /* LoadPanelOverlay15 */
    PollPanelOverlay15, /* PollPanelOverlay15 */
    func_ov002_02062f30, /* UnloadPanelOverlay15 */
    func_ov015_0206c5dc,
};

void (*gPanelSceneInitialHandler[1])(void) = {
    func_ov002_02062d94, /* PXI_Init */
};
