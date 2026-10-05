#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0xc];
    int id;
} Widget;

typedef struct {
    int stateId;
    void *focusElement;
} PanelStackEntry;

typedef struct {
    u8 pad_000[0xb70];
    PanelStackEntry stack[6];
    int depth;
    int unk_ba4;
    BOOL hasAvailableItem;
    u8 pad_bac[8];
    int lastWidgetId;
} PanelScene;

extern void *func_ov039_020bc1dc(void);
extern void func_ov027_020b9380(void *panel, Widget *widget, fx32 *position, int mode);
extern void *FindWidgetById(void *panel, int elementId);
extern void func_ov027_020b91e8(void *panel, void *element, const fx32 *position, int mode);
extern void SetInfoWindowVisible(PanelScene *scene, BOOL visible);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void MoveCursorToWidget(PanelScene *scene, Widget *widget, BOOL narrow, BOOL playSound)
{
    void *panel = func_ov039_020bc1dc();
    fx32 position[2];
    fx32 offset;

    func_ov027_020b9380(panel, widget, position, 0);
    offset = 0x30000;
    if (narrow == FALSE) {
        offset = 0x40000;
    }
    position[0] -= offset;
    func_ov027_020b91e8(panel, FindWidgetById(panel, 0), position, 0);
    switch (scene->stack[scene->depth].stateId) {
    case 1:
    case 2:
    case 3:
        if (widget->id == 2) {
            SetInfoWindowVisible(scene, scene->hasAvailableItem);
        } else {
            SetInfoWindowVisible(scene, FALSE);
        }
        break;
    }
    if (playSound && scene->lastWidgetId != widget->id) {
        PlaySoundEffect(0, 0);
    }
    scene->lastWidgetId = widget->id;
}
