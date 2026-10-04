typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#define NNS_G2D_BLKSIG_CELLBANK (u32)'CEBK'

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
typedef enum NNSG2dCharacterDataMappingType {
    NNS_G2D_CHARACTERMAPPING_1D_32,
    NNS_G2D_CHARACTERMAPPING_1D_64,
    NNS_G2D_CHARACTERMAPPING_1D_128,
    NNS_G2D_CHARACTERMAPPING_1D_256,
    NNS_G2D_CHARACTERMAPPING_2D,
    NNS_G2D_CHARACTERMAPPING_MAX
} NNSG2dCharacterDataMappingType;
typedef struct NNSG2dCellVramTransferData {
    u32 srcDataOffset;
    u32 szByte;
} NNSG2dCellVramTransferData;
typedef struct NNSG2dVramTransferData {
    u32 szByteMax;
    NNSG2dCellVramTransferData * pCellTransferDataArray;
} NNSG2dVramTransferData;
typedef struct NNSG2dCellOAMAttrData {
    u16 attr0;
    u16 attr1;
    u16 attr2;
} NNSG2dCellOAMAttrData;
typedef struct NNSG2dCellData {
    u16 numOAMAttrs;
    u16 cellAttr;
    NNSG2dCellOAMAttrData * pOamAttrArray;
} NNSG2dCellData;
typedef struct NNSG2dCellDataBank {
    u16 numCells;
    u16 cellBankAttr;
    NNSG2dCellData * pCellDataArrayHead;
    NNSG2dCharacterDataMappingType mappingMode;
    NNSG2dVramTransferData * pVramTransferData;
    void * pStringBank;
    void * pExtendedData;
} NNSG2dCellDataBank;
typedef struct NNSG2dCellDataBankBlock {
    NNSG2dBinaryBlockHeader blockHeader;
    NNSG2dCellDataBank cellDataBank;
} NNSG2dCellDataBankBlock;
void NNS_G2dUnpackNCE(NNSG2dCellDataBank * pCellData);
NNSG2dBinaryBlockHeader * NNS_G2dFindBinaryBlock(NNSG2dBinaryFileHeader * pBinFileHeader, u32 signature);
extern void NNS_G2dUnpackNCE (NNSG2dCellDataBank * pCellData);

BOOL NNS_G2dGetUnpackedCellBank (void * pNcerFile, NNSG2dCellDataBank ** ppCellBank)
{



    {
        NNSG2dBinaryFileHeader * pBinFile = (NNSG2dBinaryFileHeader *)pNcerFile;
        {
            NNSG2dCellDataBankBlock * pBinBlk =
                (NNSG2dCellDataBankBlock *)NNS_G2dFindBinaryBlock(pBinFile,
                                                                  NNS_G2D_BLKSIG_CELLBANK);
            if (pBinBlk) {
                NNS_G2dUnpackNCE((void *)&pBinBlk->cellDataBank);
                *ppCellBank = &pBinBlk->cellDataBank;
                return TRUE;
            } else {
                *ppCellBank = NULL;
                return FALSE;

            }
        }
    }
}
