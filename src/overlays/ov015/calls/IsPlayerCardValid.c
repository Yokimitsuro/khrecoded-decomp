#include "nitro/types.h"

typedef struct PlayerCard {
    u8 header[0x10];
    u16 ownName[0xb];
    u16 comment[0x1c];
    u8 macAddress[6];
    u8 budgetFlag;
    u8 modeFlag;
    u8 level;
    u8 field67;
    u8 field68;
    u8 pad69[7];
} PlayerCard;

extern u8 data_ov002_0206ada0[];
extern int GetWideStringLength(const u16 *text);
extern int GetPackedFieldValue(PlayerCard *fields, int fieldIndex, BOOL raw);

BOOL IsPlayerCardValid(PlayerCard *card)
{
    int i;
    int value;

    if (card->field68 >= 6) {
        return FALSE;
    }
    if (card->field67 >= 0x20) {
        return FALSE;
    }
    if (card->level > 99) {
        return FALSE;
    }
    if (card->modeFlag >= 11) {
        return FALSE;
    }
    if (card->budgetFlag != FALSE && card->budgetFlag != TRUE) {
        return FALSE;
    }
    if (GetWideStringLength(card->comment) >= 0x1b) {
        return FALSE;
    }
    if (GetWideStringLength(card->ownName) >= 0xb) {
        return FALSE;
    }
    for (i = 0; i < 20; i++) {
        value = GetPackedFieldValue(card, i, FALSE);
        if (i != 18) {
            if (value >= data_ov002_0206ada0[i]) {
                return FALSE;
            }
        } else if (value != -1) {
            return FALSE;
        }
    }
    return TRUE;
}
