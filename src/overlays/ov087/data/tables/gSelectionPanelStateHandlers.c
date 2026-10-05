#include "nitro/types.h"

extern void func_ov087_020c5778(void);
extern void FocusElementForState(void); /* FocusElementForState */
extern void func_ov087_020c5984(void);
extern void OpenTwoChoiceMenu(void);
extern void OpenPromptMessage0F(void); /* OpenPromptMessage0F */
extern void OpenEntryPromptForMode(void);
extern void OpenPromptMessage0E(void); /* OpenPromptMessage0E */
extern void func_ov087_020c5cb0(void);
extern void func_ov087_020c5cb4(void);
extern void OpenPromptMessage12(void); /* OpenPromptMessage12 */
extern void OpenPromptMessage10(void);
extern void OpenSelectionPanel(void); /* OpenSelectionPanel */
extern void OpenPromptMessage11(void);
extern void OpenPromptMessage13(void); /* OpenPromptMessage13 */
extern void OpenPromptMessage14(void); /* OpenPromptMessage14 */
extern void ShowVariantMessageAndSetFlag(void);
extern void ShowPromptAndStoreEntryCount(void);

void (*gSelectionPanelStateHandlers[18])(void) = {
    NULL,
    func_ov087_020c5778,
    FocusElementForState, /* FocusElementForState */
    func_ov087_020c5984,
    OpenTwoChoiceMenu,
    OpenPromptMessage0F, /* OpenPromptMessage0F */
    OpenEntryPromptForMode,
    OpenPromptMessage0E, /* OpenPromptMessage0E */
    func_ov087_020c5cb0,
    func_ov087_020c5cb4,
    OpenPromptMessage12, /* OpenPromptMessage12 */
    OpenPromptMessage10,
    OpenSelectionPanel, /* OpenSelectionPanel */
    OpenPromptMessage11,
    OpenPromptMessage13, /* OpenPromptMessage13 */
    OpenPromptMessage14, /* OpenPromptMessage14 */
    ShowVariantMessageAndSetFlag,
    ShowPromptAndStoreEntryCount,
};
