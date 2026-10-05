#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0xcc];
    fx32 speed[2];
    fx32 lane[2];
    u8 pad_0dc[0x644 - 0xdc];
    u8 primaryPanel[1];
} SceneContext;

extern void *FindWidgetById(void *panel, int elementId);
extern void func_ov027_020b9380(void *panel, void *element, fx32 *position, int mode);
extern void func_ov027_020b91e8(void *panel, void *element, const fx32 *position, int mode);
extern unsigned int func_0202a9e4(unsigned int range);
extern SceneContext *data_ov015_0207e960;

void ScrollDriftingElementsHorizontal(void) {
    fx32 position[2];
    void *panel;

    panel = data_ov015_0207e960->primaryPanel;
    func_ov027_020b9380(panel, FindWidgetById(panel, 0), position, 0);
    position[0] -= data_ov015_0207e960->speed[0];
    position[1] = data_ov015_0207e960->lane[0];
    if ((position[0] >> 12) < -0x40) {
        position[0] = 0x140000;
        data_ov015_0207e960->speed[0] = func_0202a9e4(0x1000) + 0x1000;
        data_ov015_0207e960->lane[0] = (func_0202a9e4(0x30) + 0x10) << 12;
    }
    panel = data_ov015_0207e960->primaryPanel;
    func_ov027_020b91e8(panel, FindWidgetById(panel, 0), position, 0);

    panel = data_ov015_0207e960->primaryPanel;
    func_ov027_020b9380(panel, FindWidgetById(panel, 1), position, 0);
    position[0] += data_ov015_0207e960->speed[1];
    position[1] = data_ov015_0207e960->lane[1];
    if ((position[0] >> 12) > 0x140) {
        position[0] = -0x40000;
        data_ov015_0207e960->speed[1] = func_0202a9e4(0x1000) + 0x1000;
        data_ov015_0207e960->lane[1] = (func_0202a9e4(0x30) + 0x80) << 12;
    }
    panel = data_ov015_0207e960->primaryPanel;
    func_ov027_020b91e8(panel, FindWidgetById(panel, 1), position, 0);
}
