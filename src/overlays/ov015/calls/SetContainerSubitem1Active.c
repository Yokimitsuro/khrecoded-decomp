#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x160];
    u8 container[0x6500];
} Ov015Scene;

extern Ov015Scene *data_ov015_020812e0;

extern void *FindWidgetById(void *container, int subitemId);
extern void ApplySelectedSubitemValues(void *container, void *subitem, BOOL useAlt);
extern void SetFocusedWidget(void *container, void *subitem);
extern void func_ov027_020b9640(void *container, void *subitem);
extern void func_ov027_020b9604(void *container, void *subitem);

void SetContainerSubitem1Active(BOOL active) {
    void *subitem;

    if (active) {
        subitem = FindWidgetById(data_ov015_020812e0->container, 1);
        ApplySelectedSubitemValues(data_ov015_020812e0->container, subitem, TRUE);
        subitem = FindWidgetById(data_ov015_020812e0->container, 1);
        SetFocusedWidget(data_ov015_020812e0->container, subitem);
        subitem = FindWidgetById(data_ov015_020812e0->container, 1);
        func_ov027_020b9640(data_ov015_020812e0->container, subitem);
    } else {
        subitem = FindWidgetById(data_ov015_020812e0->container, 1);
        ApplySelectedSubitemValues(data_ov015_020812e0->container, subitem, FALSE);
        SetFocusedWidget(data_ov015_020812e0->container, NULL);
        subitem = FindWidgetById(data_ov015_020812e0->container, 1);
        func_ov027_020b9604(data_ov015_020812e0->container, subitem);
    }
}
