#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0x8fc];
    s32 unk_8FC;
} Ov089Menu;

extern void *func_ov039_020bc1dc(void);
extern void func_ov027_020b9380(void *panel, int elementId, fx32 *position, int mode);
extern void *FindWidgetById(void *panel, int elementId);
extern void func_ov027_020b91e8(void *panel, void *element, const fx32 *position, int mode);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void MoveCursorToElement(Ov089Menu *menu, int elementId, BOOL playSound)
{
    void *panel = func_ov039_020bc1dc();
    fx32 position[2];
    fx32 offset;

    func_ov027_020b9380(panel, elementId, position, 0);
    offset = 0x30000;
    if (menu->unk_8FC == 0) {
        offset = 0x40000;
    }
    position[0] -= offset;
    func_ov027_020b91e8(panel, FindWidgetById(panel, 0), position, 0);
    if (playSound) {
        PlaySoundEffect(0, 0);
    }
}
