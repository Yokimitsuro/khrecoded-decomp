typedef unsigned int u32;
typedef int BOOL;

typedef struct NNSG2dBinaryFileHeader NNSG2dBinaryFileHeader;

typedef struct NNSG2dBinaryBlockHeader {
    u32 kind;
    u32 size;
} NNSG2dBinaryBlockHeader;

typedef struct NNSG2dScreenData {
    unsigned short screenWidth;
    unsigned short screenHeight;
    u32 colorMode;
    u32 screenFormat;
    u32 szByte;
    void *rawData;
} NNSG2dScreenData;

typedef struct NNSG2dScreenDataBlock {
    NNSG2dBinaryBlockHeader blockHeader;
    NNSG2dScreenData screenData;
} NNSG2dScreenDataBlock;

extern NNSG2dBinaryBlockHeader *NNS_G2dFindBinaryBlock(
    NNSG2dBinaryFileHeader *file, u32 signature);

BOOL NNS_G2dGetUnpackedScreenData(void *file, NNSG2dScreenData **screenData)
{
    NNSG2dScreenDataBlock *block =
        (NNSG2dScreenDataBlock *)NNS_G2dFindBinaryBlock(file, 0x5343524e);

    if (block != 0) {
        *screenData = &block->screenData;
        return 1;
    }

    *screenData = 0;
    return 0;
}
