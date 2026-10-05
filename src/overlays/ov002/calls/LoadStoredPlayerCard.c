#include "nitro/types.h"

typedef struct PlayerCard {
    u8 header[0x10];
    u16 name[0xb];
    u16 message[0x1b];
    u16 unk_5C;
    u8 pad_5e[6];
    u8 budgetFlag;
    u8 modeFlag;
    u8 unk_66;
    u8 unk_67;
    u8 unk_68;
    u8 unk_69;
    u8 unk_6A;
    u8 unk_6B;
    u8 unk_6C;
    u8 pad_6d[3];
} PlayerCard;

typedef struct StoredCard {
    u8 packedName[0xf];
    u8 packedMessage[0x27];
    u16 unk_36;
    u32 modeFlag : 4;
    u32 unk_66 : 5;
    u32 unk_67 : 5;
    u32 unk_68 : 3;
    u32 unk_69 : 1;
    u32 unk_bit18 : 1;
    u32 unk_6A : 1;
    u32 unk_6B : 4;
    u32 unk_6C : 1;
    u32 unk_bits25 : 7;
    u8 header[0x10];
} StoredCard;

extern StoredCard *func_ov002_02066fe0(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern int UnpackWideChars12(const u8 *packed, int packedSize, u16 *text, int textSize);

void LoadStoredPlayerCard(PlayerCard *card, int index)
{
    StoredCard *cards = func_ov002_02066fe0();

    MI_CpuFill8(card, 0, sizeof(PlayerCard));
    UnpackWideChars12(cards[index].packedName, 0xf, card->name, 0x16);
    UnpackWideChars12(cards[index].packedMessage, 0x27, card->message, 0x36);
    card->unk_5C = cards[index].unk_36;
    MI_CpuCopy8(cards[index].header, card->header, 0x10);
    card->unk_67 = cards[index].unk_67;
    card->modeFlag = cards[index].modeFlag;
    card->unk_68 = cards[index].unk_68;
    card->unk_66 = cards[index].unk_66;
    card->budgetFlag = 0;
    card->unk_69 = cards[index].unk_69;
    card->unk_6A = cards[index].unk_6A;
    card->unk_6B = cards[index].unk_6B;
    card->unk_6C = cards[index].unk_6C;
}
