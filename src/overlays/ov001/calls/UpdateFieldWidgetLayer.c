#include "nitro/types.h"

typedef struct FieldManagerHandle {
    u32 unk_00;
    void *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

extern u32 GetPanelLayerScreen(int layer);
extern int func_ov027_020b9e10(void *widget, int layer);

void UpdateFieldWidgetLayer(int layer)
{
    if (GetPanelLayerScreen(layer) == 0) {
        func_ov027_020b9e10(data_ov001_020a04c4.manager, layer);
    }
}
