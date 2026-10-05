#include "nitro/types.h"

extern void func_ov099_020bef60(void); /* HandleListCursorDown */
extern void func_ov099_020befcc(void);
extern void func_ov099_020bf038(void); /* HandleListPageDown */
extern void func_ov099_020bf0a4(void);
extern void func_ov099_020bf0fc(void);
extern void func_ov099_020bf154(void);
extern void func_ov099_020bf0cc(void);

void (*gEnemyReportListHandlers[11])(void) = {
    func_ov099_020bef60, /* HandleListCursorDown */
    func_ov099_020befcc,
    func_ov099_020bf038, /* HandleListPageDown */
    NULL,
    func_ov099_020bf0a4,
    NULL,
    NULL,
    func_ov099_020bf0fc,
    func_ov099_020bf154,
    NULL,
    func_ov099_020bf0cc,
};
