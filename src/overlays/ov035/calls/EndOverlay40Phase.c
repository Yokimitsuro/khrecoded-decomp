#include "nitro/types.h"

typedef struct MovieContext {
    u8 pad_00[0x3c];
    int loadedOverlayId;
} MovieContext;

extern MovieContext *data_ov035_020bc500;
extern void func_ov040_020bd9b0(void);
extern void func_02029fac(int processor, int overlayId);

void EndOverlay40Phase(void) {
    MovieContext *context = data_ov035_020bc500;

    func_ov040_020bd9b0();
    func_02029fac(0, context->loadedOverlayId);
    context->loadedOverlayId = -1;
}
