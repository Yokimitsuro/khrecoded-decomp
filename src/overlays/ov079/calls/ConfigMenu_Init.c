#include "nitro/types.h"

typedef struct ConfigChoice {
    const void *name;
    const void *description;
} ConfigChoice;

typedef struct ConfigOption {
    u8 count;
    u8 value;
    u16 bitWidth : 2;
    u16 locked : 1;
    u16 bitIndex : 13;
    const void *label;
    ConfigChoice choices[1];
} ConfigOption;

typedef struct ConfigPage {
    u8 rowCount;
    u8 pad_01[3];
    const void *title;
    ConfigOption *options[6];
} ConfigPage;

typedef struct TagLayout {
    u8 pad_00[2];
    s16 x;
    s16 y;
    u8 pad_06[0xa];
    int userData;
} TagLayout;

typedef struct ConfigMenu {
    u8 row;
    u8 page;
    u8 helpShown;
    u8 dirty;
    u8 pageChanged;
    u8 pad_05[3];
    void *tracker;
    void *rowTags[6];
    void *cursorTag;
    void *helpTag;
    void *headerTag;
    void *pageTabs[3];
    void *footerTag;
    void *arrowLeft;
    void *arrowRight;
    void *arrowLeftHelp;
    void *arrowRightHelp;
    ConfigPage pages[3];
    u8 objectLists[5][0x34];
    void *image;
    u8 pad_1b8[8];
} ConfigMenu;

typedef struct FrameStyle {
    u16 data[8];
} FrameStyle;

extern const FrameStyle data_ov079_020c4c30;
extern char sOv079_UiMenuStrLanguageConfigSZ_020c4ca4[];
extern void *data_0205fe0c;

extern void MI_CpuFill8(void *dest, int value, u32 size);
extern void func_ov039_020be5d8(u32 position, u32 size, int layer, void *frame, FrameStyle *style);
extern void LoadPackedFileView(void **out, const void *path, int flags);
extern void *func_ov039_020bcb40(void *save);
extern BOOL func_ov039_020bcd24(void *list, int limit, const void *text);
extern void DrawTextAnchored(void *list, int x, int y, int color, u32 flags, const void *text);
extern void *func_ov039_020bc1ac(void);
extern int func_ov039_020bc240(int slot, u32 low);
extern void func_ov027_020b7e44(void *pool, int params);
extern void *func_ov027_020ba2c8(void *messages, int index);
extern ConfigOption *func_ov079_020c4738(void *messages, int labelIndex, int count, int spec);
extern void *FindLoadedElementById(void *pool, u32 id);
extern TagLayout *FindActiveRecordById(void *pool, u32 id);
extern void *AddRecordFromTemplate(void *pool, TagLayout *source, u16 id, int userData);
extern void func_ov027_020b8208(void *pool, void *tag, s16 x, s16 y);
extern void func_ov027_020b8408(void *pool, void *tag, BOOL arm);
extern int func_ov039_020bc934(void);
extern void func_ov039_020bc338(int a, int b, int c, int d, int e, u16 f);
extern void IsPxiFifoTagSet_020bc434(int a, int b, int c);

BOOL ConfigMenu_Init(ConfigMenu *menu)
{
    FrameStyle style;
    void *title;
    void *pool;
    TagLayout *layout;
    u16 y;
    u16 x;
    u16 nextId;
    u16 i;

    MI_CpuFill8(menu, 0, sizeof(ConfigMenu));
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | 0xf00;
    style = data_ov079_020c4c30;
    func_ov039_020be5d8(0x00000008, 0x00020018, 1, menu->objectLists[0], &style);
    func_ov039_020be5d8(0x00030002, 0x0002000d, 1, menu->objectLists[1], &style);
    func_ov039_020be5d8(0x00060004, 0x000c000b, 1, menu->objectLists[2], &style);
    func_ov039_020be5d8(0x00060011, 0x000c000b, 1, menu->objectLists[3], &style);
    func_ov039_020be5d8(0x00150000, 0x00030020, 1, menu->objectLists[4], &style);
    LoadPackedFileView(&menu->image, sOv079_UiMenuStrLanguageConfigSZ_020c4ca4, 0);
    title = func_ov039_020bcb40(data_0205fe0c);
    func_ov039_020bcd24(menu->objectLists[0], 0xac, title);
    DrawTextAnchored(menu->objectLists[0], 0xbe, 2, 2, 0x20, title);
    menu->dirty = TRUE;
    pool = func_ov039_020bc1ac();
    nextId = 0x21;
    func_ov027_020b7e44(pool, func_ov039_020bc240(0, 6));

    menu->pages[0].rowCount = 6;
    menu->pages[0].title = func_ov027_020ba2c8(&menu->image, 0);
    menu->pages[0].options[0] = func_ov079_020c4738(&menu->image, 1, 2, 0x4005);
    menu->pages[0].options[1] = func_ov079_020c4738(&menu->image, 6, 2, 0x4006);
    menu->pages[0].options[2] = func_ov079_020c4738(&menu->image, 0xb, 3, 0x8003);
    menu->pages[0].options[3] = func_ov079_020c4738(&menu->image, 0x12, 2, 0x4002);
    menu->pages[0].options[4] = func_ov079_020c4738(&menu->image, 0x1c, 2, 0x4007);
    menu->pages[0].options[5] = func_ov079_020c4738(&menu->image, 0x17, 2, 0x400a);

    menu->pages[1].rowCount = 3;
    menu->pages[1].title = func_ov027_020ba2c8(&menu->image, 0x21);
    menu->pages[1].options[0] = func_ov079_020c4738(&menu->image, 0x22, 2, 0x4009);
    menu->pages[1].options[1] = func_ov079_020c4738(&menu->image, 0x27, 2, 0x4010);
    menu->pages[1].options[2] = func_ov079_020c4738(&menu->image, 0x2c, 3, 0x8012);

    menu->pages[2].rowCount = 5;
    menu->pages[2].title = func_ov027_020ba2c8(&menu->image, 0x33);
    menu->pages[2].options[0] = func_ov079_020c4738(&menu->image, 0x34, 2, 0x4011);
    menu->pages[2].options[1] = func_ov079_020c4738(&menu->image, 0x39, 2, 0x4014);
    menu->pages[2].options[2] = func_ov079_020c4738(&menu->image, 0x3e, 3, 0x800c);
    menu->pages[2].options[3] = func_ov079_020c4738(&menu->image, 0x45, 2, 0x4015);
    menu->pages[2].options[4] = func_ov079_020c4738(&menu->image, 0x4a, 2, 0x400b);

    menu->cursorTag = FindLoadedElementById(pool, 2);
    menu->helpTag = FindActiveRecordById(pool, 0x10);
    layout = FindActiveRecordById(pool, 0xd);
    menu->rowTags[0] = layout;
    for (i = 1; i < 6; i++) {
        void *tag;
        y = layout->y + i * 2;
        x = layout->x;
        tag = AddRecordFromTemplate(pool, layout, nextId++, layout->userData);
        func_ov027_020b8208(pool, tag, x, y);
        menu->rowTags[i] = tag;
    }
    menu->headerTag = FindActiveRecordById(pool, 0x16);
    for (i = 0; i < 3; i++) {
        menu->pageTabs[i] = FindLoadedElementById(pool, (u16)(i + 6));
    }
    menu->footerTag = FindActiveRecordById(pool, 0x11);
    menu->arrowLeft = FindLoadedElementById(pool, 3);
    menu->arrowRight = FindLoadedElementById(pool, 4);
    menu->arrowLeftHelp = FindActiveRecordById(pool, 0x12);
    menu->arrowRightHelp = FindActiveRecordById(pool, 0x14);
    func_ov027_020b8408(pool, menu->cursorTag, TRUE);
    func_ov027_020b8408(pool, menu->arrowLeft, TRUE);
    func_ov027_020b8408(pool, menu->arrowRight, TRUE);
    func_ov039_020bc338(0, 4, 0xc, 0x1b, 2, func_ov039_020bc934());
    IsPxiFifoTagSet_020bc434(1, 0, 0xc0);
    menu->tracker = pool;
    menu->dirty = 2;
    menu->pageChanged = 2;
    return TRUE;
}
