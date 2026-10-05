#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x40];
    u8 listLayer[0xb4];
    void *selectedNode;
    u8 pad_0f8[0x134 - 0xf8];
    int pageIndex;
    u8 pad_138[0x154 - 0x138];
    BOOL arrowsVisible;
    u8 pad_158[0x190 - 0x158];
    u8 recordPool[0x58];
    u8 visitedPages;
} Ov086Menu;

extern u8 *func_ov039_020bc1ec(void);
extern void *FindWidgetById(u8 *panel, int elementId);
extern void SetEntrySlotsVisible(u8 *panel, void *element, BOOL visible);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8230(void *pool, void *record);
extern void SelectListNodeOrFirst(void *self, void *target);
extern void Text_UploadTileBuffer(void *surface);

void ShowPrimaryRecordList(Ov086Menu *menu)
{
    u8 *panel = func_ov039_020bc1ec();

    menu->arrowsVisible = FALSE;
    func_ov027_020b8230(menu->recordPool, FindActiveRecordById(menu->recordPool, 0x3ea));
    SetEntrySlotsVisible(panel, FindWidgetById(panel, 0x14), FALSE);
    SetEntrySlotsVisible(panel, FindWidgetById(panel, 0x15), FALSE);
    SetEntrySlotsVisible(panel, FindWidgetById(panel, 0x2d), FALSE);
    SetEntrySlotsVisible(panel, FindWidgetById(panel, 0x2e), FALSE);
    SelectListNodeOrFirst(menu->listLayer, menu->selectedNode);
    Text_UploadTileBuffer(menu->listLayer);
    if (menu->visitedPages & (1 << menu->pageIndex)) {
        func_ov027_020b8230(menu->recordPool, FindActiveRecordById(menu->recordPool, 0x3ed));
    } else {
        func_ov027_020b8230(menu->recordPool, FindActiveRecordById(menu->recordPool, 0x3ef));
    }
}
