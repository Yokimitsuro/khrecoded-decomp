#include "nitro/types.h"

typedef struct {
    int format;
    BOOL isExtendedPalette;
    u32 sizeBytes;
    u8 *rawData;
} PaletteData;

typedef struct {
    int format;
    BOOL isExtendedPalette;
    u32 vramAddress[3];
} PaletteProxy;

extern char sOv002_WxcAvtAvtP2_0206c438[];
extern void NNS_G2dInitImagePaletteProxy(PaletteProxy *proxy);
extern BOOL NNS_G2dGetUnpackedPaletteData(void *nclrFile, PaletteData **outPalette);
extern void NNS_G2dLoadPalette(PaletteData *palette, u32 vramOffset, int vramType, PaletteProxy *proxy);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void *Archive_LoadFile(u32 fileId, u32 flags);
extern int Msg_OpenContainerAndReadHeader(const char *path, u32 kind, u32 fromTop);
extern void ZeroHalfThenFree(int handle);
extern void func_0202d328(void *archive, int extra);
extern void *NestedPointer_GetFirstWord(void *archive, int recordIndex, int entryIndex);

void LoadAvatarObjPalette(BOOL useSubScreen)
{
    int fileHandle;
    void *archive;
    void *nclrFile;
    int vramType;
    PaletteData *palette;
    PaletteProxy proxy;

    NNS_G2dInitImagePaletteProxy(&proxy);
    fileHandle = Msg_OpenContainerAndReadHeader(sOv002_WxcAvtAvtP2_0206c438, 0x10, 0);
    archive = Archive_LoadFile((fileHandle + 0x8000U & 0xfffffc) << 7 | 0x80000000, 0x10);
    vramType = 1;
    func_0202d328(archive, 1);
    nclrFile = NestedPointer_GetFirstWord(archive, 0, 0);
    if (nclrFile != NULL) {
        NNS_G2dGetUnpackedPaletteData(nclrFile, &palette);
        if (palette->isExtendedPalette) {
            palette->sizeBytes -= 0x200;
            if (useSubScreen) {
                vramType = 2;
            }
            palette->rawData += 0x200;
            NNS_G2dLoadPalette(palette, 0x200, vramType, &proxy);
        }
    }
    if (archive != NULL) {
        NNSi_FndFreeFromDefaultHeap(archive);
    }
    ZeroHalfThenFree(fileHandle);
}
