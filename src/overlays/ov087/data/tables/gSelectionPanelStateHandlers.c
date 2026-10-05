#include "nitro/types.h"

extern void func_ov087_020c5778(void);
extern void func_ov087_020c5880(void); /* FocusElementForState */
extern void func_ov087_020c5984(void);
extern void func_ov087_020c5a94(void);
extern void func_ov087_020c5b40(void); /* OpenPromptMessage0F */
extern void func_ov087_020c5bc0(void);
extern void func_ov087_020c5c64(void); /* OpenPromptMessage0E */
extern void func_ov087_020c5cb0(void);
extern void func_ov087_020c5cb4(void);
extern void func_ov087_020c5cb8(void); /* OpenPromptMessage12 */
extern void func_ov087_020c5d04(void);
extern void func_ov087_020c5d64(void); /* OpenSelectionPanel */
extern void func_ov087_020c5e18(void);
extern void func_ov087_020c5e78(void); /* OpenPromptMessage13 */
extern void func_ov087_020c5ec4(void); /* OpenPromptMessage14 */
extern void func_ov087_020c49b0(void);
extern void func_ov087_020c4a1c(void);

void (*gSelectionPanelStateHandlers[18])(void) = {
    NULL,
    func_ov087_020c5778,
    func_ov087_020c5880, /* FocusElementForState */
    func_ov087_020c5984,
    func_ov087_020c5a94,
    func_ov087_020c5b40, /* OpenPromptMessage0F */
    func_ov087_020c5bc0,
    func_ov087_020c5c64, /* OpenPromptMessage0E */
    func_ov087_020c5cb0,
    func_ov087_020c5cb4,
    func_ov087_020c5cb8, /* OpenPromptMessage12 */
    func_ov087_020c5d04,
    func_ov087_020c5d64, /* OpenSelectionPanel */
    func_ov087_020c5e18,
    func_ov087_020c5e78, /* OpenPromptMessage13 */
    func_ov087_020c5ec4, /* OpenPromptMessage14 */
    func_ov087_020c49b0,
    func_ov087_020c4a1c,
};
