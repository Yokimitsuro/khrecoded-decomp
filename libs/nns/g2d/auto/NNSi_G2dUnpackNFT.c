typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

#define NULL ((void *)0)

#define NNS_G2D_BINBLK_SIG_FINFDATA 0x46494e46
#define NNS_G2D_BINBLK_SIG_CGLPDATA 0x43474c50
#define NNS_G2D_BINBLK_SIG_CWDHDATA 0x43574448
#define NNS_G2D_BINBLK_SIG_CMAPDATA 0x434d4150

typedef struct NNSG2dBinaryFileHeader {
    u32 signature;
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
} NNSG2dBinaryFileHeader;

typedef struct NNSG2dBinaryBlockHeader {
    u32 kind;
    u32 size;
} NNSG2dBinaryBlockHeader;

typedef struct NNSG2dCharWidths {
    s8 left;
    u8 glyphWidth;
    s8 charWidth;
} NNSG2dCharWidths;

typedef struct NNSG2dFontGlyph NNSG2dFontGlyph;

typedef struct NNSG2dFontWidth {
    u16 indexBegin;
    u16 indexEnd;
    struct NNSG2dFontWidth *pNext;
    NNSG2dCharWidths widthTable[];
} NNSG2dFontWidth;

typedef struct NNSG2dFontCodeMap {
    u16 ccodeBegin;
    u16 ccodeEnd;
    u16 mappingMethod;
    u16 reserved;
    struct NNSG2dFontCodeMap *pNext;
    u16 mapInfo[];
} NNSG2dFontCodeMap;

typedef struct NNSG2dFontInformation {
    u8 fontType;
    s8 linefeed;
    u16 alterCharIndex;
    NNSG2dCharWidths defaultWidth;
    u8 encoding;
    NNSG2dFontGlyph *pGlyph;
    NNSG2dFontWidth *pWidth;
    NNSG2dFontCodeMap *pMap;
} NNSG2dFontInformation;

inline void ResolveOffset(void **ppOffset, void *pBase)
{
    *ppOffset = (void *)(*(u32 *)ppOffset + (u32)pBase);
}

void NNSi_G2dUnpackNFT(NNSG2dBinaryFileHeader *pHeader)
{
    NNSG2dBinaryBlockHeader *pBlock;
    NNSG2dFontInformation *pInfo = NULL;

    {
        int nBlocks = 0;
        pBlock = (NNSG2dBinaryBlockHeader *)((u8 *)pHeader + pHeader->headerSize);

        while (nBlocks < pHeader->dataBlocks) {
            switch (pBlock->kind) {
            case NNS_G2D_BINBLK_SIG_FINFDATA:
                {
                    pInfo = (NNSG2dFontInformation *)((u8 *)pBlock + sizeof(*pBlock));

                    ResolveOffset((void **)&pInfo->pGlyph, pHeader);

                    if (pInfo->pWidth != NULL) {
                        ResolveOffset((void **)&pInfo->pWidth, pHeader);
                    }
                    if (pInfo->pMap != NULL) {
                        ResolveOffset((void **)&pInfo->pMap, pHeader);
                    }
                }
                break;
            case NNS_G2D_BINBLK_SIG_CGLPDATA:
                break;
            case NNS_G2D_BINBLK_SIG_CWDHDATA:
                {
                    NNSG2dFontWidth *pWidth =
                        (NNSG2dFontWidth *)((u8 *)pBlock + sizeof(*pBlock));

                    if (pWidth->pNext != NULL) {
                        ResolveOffset((void **)&pWidth->pNext, pHeader);
                    }
                }
                break;
            case NNS_G2D_BINBLK_SIG_CMAPDATA:
                {
                    NNSG2dFontCodeMap *pMap =
                        (NNSG2dFontCodeMap *)((u8 *)pBlock + sizeof(*pBlock));

                    if (pMap->pNext != NULL) {
                        ResolveOffset((void **)&pMap->pNext, pHeader);
                    }
                }
                break;
            default:
                break;
            }

            pBlock = (NNSG2dBinaryBlockHeader *)((u8 *)pBlock + pBlock->size);
            nBlocks++;
        }
    }
}
