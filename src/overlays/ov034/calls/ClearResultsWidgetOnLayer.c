#include "nitro/types.h"

typedef struct ResultsWork {
    u8 pad_0000[0x64d8];
    u8 screenLayers[0x1c];
} ResultsWork;

typedef struct ResultsScreen {
    void *params;
    ResultsWork *work;
} ResultsScreen;

extern ResultsScreen data_ov034_020c0fa0;
extern void func_ov027_020b9bb4(void *layers, void *widget);

void ClearResultsWidgetOnLayer(void *widget)
{
    func_ov027_020b9bb4(data_ov034_020c0fa0.work->screenLayers, widget);
}
