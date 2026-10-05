#include "nitro/types.h"

typedef struct {
    s8 mode;
} SceneContext;

extern void ScrollDriftingElementsHorizontal(void);
extern void ScrollDriftingElementsVertical(void);
extern SceneContext *data_ov015_0207e960;

void UpdateDriftingElementsByMode(void) {
    switch (data_ov015_0207e960->mode) {
    case 0:
    case 1:
    case 7:
        ScrollDriftingElementsHorizontal();
        break;
    case 2:
    case 3:
    case 6:
        ScrollDriftingElementsVertical();
        break;
    }
}
