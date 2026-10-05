#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct CharacterSet {
    u8 pad_00[0x38];
    void *file;
    NNSG2dCharacterData *character;
    void *frames[3];
} CharacterSet;

extern u32 MakePrimaryVramKey(u32 index);
extern u32 MakePrimaryVramKey_02071214(u32 index);
extern void *func_0202c4a0(u32 fileId, u32 heapId);
extern void *Archive_LoadFile(u32 fileId, u32 heapId);
extern BOOL NNS_G2dGetUnpackedBGCharacterData(void *file, NNSG2dCharacterData **character);
extern void DC_FlushRange(void *buffer, u32 size);
extern void GX_LoadBG2Char(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void LoadBg2CharAndFrames(CharacterSet *set)
{
    void *file;
    NNSG2dCharacterData *character;

    file = func_0202c4a0(MakePrimaryVramKey(6), 0xe);
    NNS_G2dGetUnpackedBGCharacterData(file, &character);
    DC_FlushRange(character->pRawData, character->szByte);
    GX_LoadBG2Char(character->pRawData, 0, character->szByte);
    NNSi_FndFreeFromDefaultHeap(file);
    set->file = Archive_LoadFile(MakePrimaryVramKey_02071214(2), 0xe);
    NNS_G2dGetUnpackedBGCharacterData(set->file, &set->character);
    set->frames[0] = set->character->pRawData;
    set->frames[1] = (u8 *)set->character->pRawData + 0x300;
    set->frames[2] = (u8 *)set->character->pRawData + 0x600;
}
