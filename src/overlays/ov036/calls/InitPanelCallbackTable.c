#include "nitro/types.h"

typedef void (*PanelCallback)(void);

typedef struct PanelCallbackTable {
    PanelCallback callbacks[9];
} PanelCallbackTable;

extern void func_ov036_020bc3a4(void);
extern void IsSceneReady(void);
extern void func_ov036_020bc3f4(void);
extern void SetSceneFlag4000(void);
extern void IsPxiFifoTagSet_020bc434(void);
extern void InvalidatePxiFifoTag(void);
extern void RecordPanelInputEvent(void);
extern void func_ov036_020bc4c0(void);
extern void func_ov036_020bb2a4(void);

void InitPanelCallbackTable(PanelCallbackTable *table)
{
    table->callbacks[0] = func_ov036_020bc3a4;
    table->callbacks[1] = IsSceneReady;
    table->callbacks[2] = func_ov036_020bc3f4;
    table->callbacks[3] = SetSceneFlag4000;
    table->callbacks[4] = IsPxiFifoTagSet_020bc434;
    table->callbacks[5] = InvalidatePxiFifoTag;
    table->callbacks[6] = RecordPanelInputEvent;
    table->callbacks[7] = func_ov036_020bc4c0;
    table->callbacks[8] = func_ov036_020bb2a4;
}
