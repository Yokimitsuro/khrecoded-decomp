#include "nitro/types.h"

extern void func_ov002_02065070(void);
extern void func_ov002_02065074(void); /* ResetMenuElement5 */
extern void func_ov002_020650e0(void); /* UpdateMenuTouchSelect */
extern void func_ov002_020651c0(void); /* CloseMenuElement5 */
extern void func_ov002_02065244(void); /* OpenMenuSelector */
extern void func_ov002_02065374(void); /* UpdateSaveMenuState */
extern void func_ov002_02065668(void); /* CloseMenuPopup */
extern void func_ov002_0206574c(void); /* OpenMenuPopup */
extern void func_ov002_020658c0(void); /* UpdateQuitMenuState */
extern void ReleaseMenuPanelCallback(void); /* ReleaseMenuPanelCallback */
extern void func_ov002_02065c1c(void); /* OSi_IrqDma3 */
extern void func_ov002_02065c2c(void);
extern void func_ov002_02065c30(void);
extern void func_ov002_02065c34(void); /* OSi_IrqDma3 */
extern void func_ov002_02065c44(void);
extern void func_ov002_02065c48(void);
extern void func_ov002_02064ff8(void); /* RunMenuIntroStep */

void (*gMenuStateHandlers[16])(void) = {
    func_ov002_02065070,
    func_ov002_02065074, /* ResetMenuElement5 */
    func_ov002_020650e0, /* UpdateMenuTouchSelect */
    func_ov002_020651c0, /* CloseMenuElement5 */
    func_ov002_02065244, /* OpenMenuSelector */
    func_ov002_02065374, /* UpdateSaveMenuState */
    func_ov002_02065668, /* CloseMenuPopup */
    func_ov002_0206574c, /* OpenMenuPopup */
    func_ov002_020658c0, /* UpdateQuitMenuState */
    ReleaseMenuPanelCallback, /* ReleaseMenuPanelCallback */
    func_ov002_02065c1c, /* OSi_IrqDma3 */
    func_ov002_02065c2c,
    func_ov002_02065c30,
    func_ov002_02065c34, /* OSi_IrqDma3 */
    func_ov002_02065c44,
    func_ov002_02065c48,
};

void (*gMenuInitialStateHandler[1])(void) = {
    func_ov002_02064ff8, /* RunMenuIntroStep */
};
