#include "nitro/types.h"

extern void func_ov002_02065070(void);
extern void ResetMenuElement5(void); /* ResetMenuElement5 */
extern void UpdateMenuTouchSelect(void); /* UpdateMenuTouchSelect */
extern void CloseMenuElement5(void); /* CloseMenuElement5 */
extern void OpenMenuSelector(void); /* OpenMenuSelector */
extern void UpdateSaveMenuState(void); /* UpdateSaveMenuState */
extern void CloseMenuPopup(void); /* CloseMenuPopup */
extern void OpenMenuPopup(void); /* OpenMenuPopup */
extern void UpdateQuitMenuState(void); /* UpdateQuitMenuState */
extern void ReleaseMenuPanelCallback(void); /* ReleaseMenuPanelCallback */
extern void func_ov002_02065c1c(void); /* OSi_IrqDma3 */
extern void func_ov002_02065c2c(void);
extern void func_ov002_02065c30(void);
extern void func_ov002_02065c34(void); /* OSi_IrqDma3 */
extern void func_ov002_02065c44(void);
extern void func_ov002_02065c48(void);
extern void RunMenuIntroStep(void); /* RunMenuIntroStep */

void (*gMenuStateHandlers[16])(void) = {
    func_ov002_02065070,
    ResetMenuElement5, /* ResetMenuElement5 */
    UpdateMenuTouchSelect, /* UpdateMenuTouchSelect */
    CloseMenuElement5, /* CloseMenuElement5 */
    OpenMenuSelector, /* OpenMenuSelector */
    UpdateSaveMenuState, /* UpdateSaveMenuState */
    CloseMenuPopup, /* CloseMenuPopup */
    OpenMenuPopup, /* OpenMenuPopup */
    UpdateQuitMenuState, /* UpdateQuitMenuState */
    ReleaseMenuPanelCallback, /* ReleaseMenuPanelCallback */
    func_ov002_02065c1c, /* OSi_IrqDma3 */
    func_ov002_02065c2c,
    func_ov002_02065c30,
    func_ov002_02065c34, /* OSi_IrqDma3 */
    func_ov002_02065c44,
    func_ov002_02065c48,
};

void (*gMenuInitialStateHandler[1])(void) = {
    RunMenuIntroStep, /* RunMenuIntroStep */
};
