#include "nitro/types.h"

extern BOOL func_ov001_02063838(void);
extern BOOL TryActivateAllActors(void);
extern int func_ov001_02063a38(void);
extern BOOL func_ov036_020bc688(void);

BOOL func_0202852c(void) {
    if (func_ov001_02063838() != 0 && TryActivateAllActors() != 0) {
        return 1;
    }
    if (func_ov001_02063a38() == 8 && func_ov036_020bc688() != 0) {
        return 1;
    }
    return 0;
}
