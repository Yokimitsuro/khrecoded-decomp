#include "nitro/types.h"

extern void HandleListCursorDown(void); /* HandleListCursorDown */
extern void func_ov099_020befcc(void);
extern void HandleListPageDown(void); /* HandleListPageDown */
extern void func_ov099_020bf0a4(void);
extern void CloseSubBgPanel(void);
extern void OpenSubBgPanel(void);
extern void func_ov099_020bf0cc(void);

void (*gEnemyReportListHandlers[11])(void) = {
    HandleListCursorDown, /* HandleListCursorDown */
    func_ov099_020befcc,
    HandleListPageDown, /* HandleListPageDown */
    NULL,
    func_ov099_020bf0a4,
    NULL,
    NULL,
    CloseSubBgPanel,
    OpenSubBgPanel,
    NULL,
    func_ov099_020bf0cc,
};
