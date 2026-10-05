#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u32 value;
} PanelItem;

typedef struct {
    u8 pad_00[0x6ac0];
    u8 container[4];
} PanelState;

extern PanelItem *FindWidgetById(void *container, int itemId);
extern void SetEntrySlotsVisible(void *container, PanelItem *item, int flag);
extern void ApplySelectedSubitemValues(void *container, PanelItem *item, int useAlt);
extern void func_ov027_020b90b8(void *container, u32 callback);
extern void func_ov027_020b9640(void *container, PanelItem *item);
extern void func_ov002_020620fc(int mode);
extern PanelState *data_ov015_0207e960;

void HidePanelOptionSlots(void) {
    void *container;

    func_ov002_020620fc(0);
    container = data_ov015_0207e960->container;
    SetEntrySlotsVisible(container, FindWidgetById(container, 4), 0);
    container = data_ov015_0207e960->container;
    SetEntrySlotsVisible(container, FindWidgetById(container, 7), 0);
    container = data_ov015_0207e960->container;
    ApplySelectedSubitemValues(container, FindWidgetById(container, 7), 0);
    container = data_ov015_0207e960->container;
    SetEntrySlotsVisible(container, FindWidgetById(container, 8), 0);
    container = data_ov015_0207e960->container;
    ApplySelectedSubitemValues(container, FindWidgetById(container, 8), 0);
    container = data_ov015_0207e960->container;
    ApplySelectedSubitemValues(container, FindWidgetById(container, 1), 1);
    container = data_ov015_0207e960->container;
    ApplySelectedSubitemValues(container, FindWidgetById(container, 2), 1);
    container = data_ov015_0207e960->container;
    ApplySelectedSubitemValues(container, FindWidgetById(container, 3), 1);
    func_ov027_020b90b8(data_ov015_0207e960->container, 0);
    container = data_ov015_0207e960->container;
    func_ov027_020b9640(container, FindWidgetById(container, 9));
}
