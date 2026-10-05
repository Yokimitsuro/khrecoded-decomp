#include "nitro/types.h"

typedef struct {
    s8 mode;
} SceneContext;

extern void func_ov015_0206fff0(void);
extern void func_ov015_02070174(void);
extern SceneContext *data_ov015_0207e960;

void UpdateDriftingElementsByMode(void) {
    switch (data_ov015_0207e960->mode) {
    case 0:
    case 1:
    case 7:
        func_ov015_0206fff0();
        break;
    case 2:
    case 3:
    case 6:
        func_ov015_02070174();
        break;
    }
}
