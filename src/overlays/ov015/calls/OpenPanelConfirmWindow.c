#include "nitro/types.h"

typedef struct BgGraphicsData {
    void *screen;
    void *character;
    void *palette;
} BgGraphicsData;

typedef struct PanelWork {
    u8 pad_0000[0x65e0];
    int textBank[5];
    void *tileObject;
} PanelWork;

extern char sOv015_WxcSchP2_0207e8ac[];
extern PanelWork *data_ov015_020812e0;

extern int Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern void *func_0202c4a0(u32 fileId, u32 type);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void *G2S_GetBG2ScrPtr(void);
extern void *G2S_GetBG2CharPtr(void);
extern void NNS_G2dBGLoadScreenRect(void *dst, void *screen, int srcX, int srcY, int dstX, int dstY,
                                             int dstW, int dstH, int width, int height);
extern void DestroyOwnedObjectList(void **slot);
extern u32 GetPanelSlot0(void);
extern void *CreateTileObject(u32 ownerId, u32 value, u16 *layout, void *tileData, void *mapData);
extern void func_ov015_020789b8(void *object, int x, int y, int color, int width, const void *text);
extern void *func_ov027_020ba2c8(int *bank, int index);
extern int CountTextLines(const u16 *text);
extern void Text_UploadTileBuffer(void *surface);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void ZeroHalfThenFree(int handle);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void OpenPanelConfirmWindow(int x, int y, const u16 *message)
{
    BgGraphicsData bgData;
    u16 layout[8];
    int handle;
    void *archive;
    u32 slot;
    void *charPtr;

    handle = Msg_OpenContainerAndReadHeader(sOv015_WxcSchP2_0207e8ac, 0x10, 0);
    archive = func_0202c4a0(((handle + 0x8000U) & 0xfffffc) << 7 | 0x80000001, 0x10);
    GetBgDataFromArchive(&bgData, archive, 0, -1, -1);
    NNS_G2dBGLoadScreenRect(G2S_GetBG2ScrPtr(), bgData.screen, 0, 0, x, y, 0x20, 0x20, 0x1a, 0xa);
    layout[0] = x + 2;
    layout[1] = y + 2;
    layout[2] = 0x16;
    layout[3] = 6;
    layout[4] = 0x32d;
    layout[5] = 0;
    layout[6] = 0;
    layout[7] = 2;
    DestroyOwnedObjectList(&data_ov015_020812e0->tileObject);
    slot = GetPanelSlot0();
    charPtr = G2S_GetBG2CharPtr();
    data_ov015_020812e0->tileObject = CreateTileObject(6, slot, layout, charPtr, G2S_GetBG2ScrPtr());
    func_ov015_020789b8(data_ov015_020812e0->tileObject, 0x28, 0x27, 0xf, 0x12, func_ov027_020ba2c8(data_ov015_020812e0->textBank, 10));
    func_ov015_020789b8(data_ov015_020812e0->tileObject, 0x88, 0x27, 0xf, 0x12, func_ov027_020ba2c8(data_ov015_020812e0->textBank, 11));
    func_ov015_020789b8(data_ov015_020812e0->tileObject, -1, (0x18 - CountTextLines(message) * 0xc) / 2, 0xf, 0, message);
    Text_UploadTileBuffer(data_ov015_020812e0->tileObject);
    if (archive != NULL) {
        NNSi_FndFreeFromDefaultHeap(archive);
    }
    ZeroHalfThenFree(handle);
    PlaySoundEffect(2, 3);
}
