#include "nitro/types.h"

extern void func_ov087_020c5778(void);
extern void func_ov087_020c5880(void); /* FocusElementForState */
extern void func_ov087_020c5984(void);
extern void func_ov087_020c5a94(void);
extern void func_ov087_020c5b40(void); /* OpenPromptMessage0F */
extern void func_ov087_020c5bc0(void);
extern void OpenPromptMessage0E(void); /* OpenPromptMessage0E */
extern void func_ov087_020c5cb0(void);
extern void func_ov087_020c5cb4(void);
extern void OpenPromptMessage12(void); /* OpenPromptMessage12 */
extern void OpenPromptMessage10(void);
extern void func_ov087_020c5d64(void); /* OpenSelectionPanel */
extern void OpenPromptMessage11(void);
extern void OpenPromptMessage13(void); /* OpenPromptMessage13 */
extern void OpenPromptMessage14(void); /* OpenPromptMessage14 */
extern void func_ov087_020c49b0(void);
extern void ShowPromptAndStoreEntryCount(void);

void (*gSelectionPanelStateHandlers[18])(void) = {
    NULL,
    func_ov087_020c5778,
    func_ov087_020c5880, /* FocusElementForState */
    func_ov087_020c5984,
    func_ov087_020c5a94,
    func_ov087_020c5b40, /* OpenPromptMessage0F */
    func_ov087_020c5bc0,
    OpenPromptMessage0E, /* OpenPromptMessage0E */
    func_ov087_020c5cb0,
    func_ov087_020c5cb4,
    OpenPromptMessage12, /* OpenPromptMessage12 */
    OpenPromptMessage10,
    func_ov087_020c5d64, /* OpenSelectionPanel */
    OpenPromptMessage11,
    OpenPromptMessage13, /* OpenPromptMessage13 */
    OpenPromptMessage14, /* OpenPromptMessage14 */
    func_ov087_020c49b0,
    ShowPromptAndStoreEntryCount,
};
