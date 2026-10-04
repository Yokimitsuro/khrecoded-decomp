typedef unsigned short u16;
typedef unsigned int u32;

typedef struct NNSG2dUserExCellAttr {
    u32 *pAttr;
} NNSG2dUserExCellAttr;

typedef struct NNSG2dUserExCellAttrBank {
    u16 numCells;
    u16 numAttribute;
    NNSG2dUserExCellAttr *pCellAttrArray;
} NNSG2dUserExCellAttrBank;

void NNSi_G2dUnpackUserExCellAttrBank(NNSG2dUserExCellAttrBank *cellAttrBank)
{
    u16 i;

    cellAttrBank->pCellAttrArray =
        (NNSG2dUserExCellAttr *)((u32)cellAttrBank->pCellAttrArray + (u32)cellAttrBank);
    for (i = 0; i < cellAttrBank->numCells; i++) {
        cellAttrBank->pCellAttrArray[i].pAttr =
            (u32 *)((u32)cellAttrBank->pCellAttrArray[i].pAttr + (u32)cellAttrBank);
    }
}
