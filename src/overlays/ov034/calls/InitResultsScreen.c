#include "nitro/types.h"

typedef struct ResultsWork {
    u8 pad_0000[0x10];
    u8 tagTracker[0x4c];
    u8 objects[0x647c];
    u8 iconLayer[0x20];
    int isActive;
    u8 pad_64fc[0x640];
    u8 messages[0xc];
    u8 font[0xc];
    u8 fontAlt[0xc];
    u8 text[0x68];
    u32 mode;
    u8 pad_6bcc[0x178];
    int badgeEntry;
    int rowEntries[6];
} ResultsWork;

typedef struct ResultsScreen {
    void *params;
    ResultsWork *work;
} ResultsScreen;

typedef struct TextFrame {
    u16 values[8];
} TextFrame;

typedef struct TagConfig {
    u32 values[5];
} TagConfig;

typedef struct ObjConfig {
    u32 fileId;
    u32 values[3];
} ObjConfig;

typedef struct PaletteData {
    u8 pad_00[8];
    u32 size;
    void *data;
} PaletteData;

typedef struct CharacterData {
    u8 pad_00[0x10];
    u32 size;
    void *data;
} CharacterData;

typedef struct BgGraphicsData {
    void *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

extern ResultsScreen data_ov034_020c0fa0;
extern char sOv034_UiBtlStrLanguageP2_020c0ea8[];
extern char data_ov034_020c0eb8[];
extern char data_ov034_020c0ed0[];
extern char sOv034_UiBtlBtluiP2_020c0ee8[];
extern char sOv034_UiBtlBtlLanguageP2_020c0efc[];
extern TextFrame data_ov034_020be8dc;
extern TagConfig data_ov034_020be8ec;
extern ObjConfig data_ov034_020be8bc;
extern u8 sOv034_SYSAREAMENU_020c0f10[];

extern void EnterResultsTierMode(u32 mode);
extern u32 Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern void LoadPackedFileView(void *view, u32 fileId, BOOL fromTail);
extern int ZeroHalfThenFree(u32 container);
extern int func_0200146c(void *font, char *path);
extern u16 *func_ov027_020b9e10(void *layer, int id);
extern BOOL InitTextLayerAt(void *text, int layer, u16 *screenBase, void *font, TextFrame *frame);
extern void func_ov027_020b9e20(void *layer, int id);
extern int AcquireRecordSlot(int slot, int param);
extern void func_ov027_020b7d78(void *tracker, TagConfig *config);
extern void func_ov027_020b7e44(void *tracker, u32 fileId);
extern void *func_0202c4a0(u32 fileId, u32 mode);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void GX_LoadBGPltt(void *src, u32 offset, u32 size);
extern void GX_LoadBG3Char(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern int InitializeResourceContainer(void *container, void *params);
extern void InitObjManagerAndMark(void *objects, ObjConfig *config);
extern void func_ov027_020b9098(void *objects, u32 fileId);
extern void func_ov027_020b8fb8(void *objects, u32 fileId, int count);
extern void SetAllElementObjectModes(void *objects, int mode);
extern void *FindWidgetById(void *objects, int id);
extern void func_ov027_020b97d8(void *objects, void *widget, int mode);
extern void SetWidgetRootDpadEnabled(void *objects, BOOL enabled);
extern int func_ov034_020bdea8(void *manager, int animation, int resource, int x, int y);
extern void func_ov027_020b90b8(void *objects, void (*callback)(void));
extern void func_ov034_020bd130(void);
extern void InvokeForChannelOrBoth(u32 arg0, void *arg1, void (*callback)(void), int channel);
extern void UpdateResultsFade(void);

#define WORK (data_ov034_020c0fa0.work)
#define CONTAINER_BASE(container) ((((container) + 0x8000) & 0xfffffc) << 7)

void InitResultsScreen(void)
{
    u32 container;
    u32 objContainer;
    u32 iconContainer;
    u32 base;
    void *archive;
    BgGraphicsData bg;
    TagConfig tagConfig;
    ObjConfig objConfig;
    TextFrame frame;
    int i;

    EnterResultsTierMode(WORK->mode);
    container = Msg_OpenContainerAndReadHeader(sOv034_UiBtlStrLanguageP2_020c0ea8, 0xe, 0);
    LoadPackedFileView(WORK->messages, CONTAINER_BASE(container) | 0x80000007, 1);
    ZeroHalfThenFree(container);
    func_0200146c(WORK->font, data_ov034_020c0eb8);
    func_0200146c(WORK->fontAlt, data_ov034_020c0ed0);
    frame = data_ov034_020be8dc;
    InitTextLayerAt(WORK->text, 2, func_ov027_020b9e10(WORK->iconLayer, 10), WORK->font, &frame);
    func_ov027_020b9e20(WORK->iconLayer, 10);
    AcquireRecordSlot(0, 0);
    objContainer = Msg_OpenContainerAndReadHeader(sOv034_UiBtlBtluiP2_020c0ee8, 0xe, 0);
    iconContainer = Msg_OpenContainerAndReadHeader(sOv034_UiBtlBtlLanguageP2_020c0efc, 0xe, 0);
    tagConfig = data_ov034_020be8ec;
    func_ov027_020b7d78(WORK->tagTracker, &tagConfig);
    base = CONTAINER_BASE(objContainer);
    func_ov027_020b7e44(WORK->tagTracker, base | 0x80000011);
    archive = func_0202c4a0(base | 0x80000012, 0xe);
    GetBgDataFromArchive(&bg, archive, -1, 0, 0);
    GX_LoadBGPltt(bg.palette->data, 0, bg.palette->size);
    GX_LoadBG3Char(bg.character->data, 0, bg.character->size);
    if (archive != NULL) {
        NNSi_FndFreeFromDefaultHeap(archive);
    }
    objConfig = data_ov034_020be8bc;
    objConfig.fileId = base | 0x80000015;
    InitializeResourceContainer(WORK->objects, NULL);
    InitObjManagerAndMark(WORK->objects, &objConfig);
    func_ov027_020b9098(WORK->objects, CONTAINER_BASE(iconContainer) | 0x8000001a);
    func_ov027_020b8fb8(WORK->objects, base | 0x80000016, 0x4a);
    SetAllElementObjectModes(WORK->objects, 1);
    func_ov027_020b97d8(WORK->objects, FindWidgetById(WORK->objects, 200), 0);
    SetWidgetRootDpadEnabled(WORK->objects, TRUE);
    ZeroHalfThenFree(objContainer);
    ZeroHalfThenFree(iconContainer);
    WORK->badgeEntry = func_ov034_020bdea8(WORK->objects, 1, 9, 0x80, 100);
    for (i = 0; i < 6; i++) {
        WORK->rowEntries[i] = func_ov034_020bdea8(WORK->objects, 1, 0xc, 0xb8, i * 16 + 0x51);
    }
    func_ov027_020b90b8(WORK->objects, func_ov034_020bd130);
    InvokeForChannelOrBoth(1, sOv034_SYSAREAMENU_020c0f10, UpdateResultsFade, 0);
    WORK->isActive = 1;
}
