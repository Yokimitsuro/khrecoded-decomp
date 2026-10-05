#include "nitro/types.h"

typedef struct {
    u32 words[4];
} Block16;

typedef struct {
    Block16 header;
    u8 ownName[0x16];
    u8 otherName[0x16];
    u8 pad3c[0x22];
    u8 macAddress[6];
    u8 budgetFlag;
    u8 modeFlag;
    u8 pad66;
    s8 field67;
    s8 field68;
    u8 pad69[2];
    u8 field6b;
    u8 padEnd[4];
} PlayerCard;

extern void MI_CpuFill8(void *dst, int val, unsigned int n);
extern void OS_GetMacAddress(u8 *address);
extern s8 *data_ov015_0207e960;
extern int DispatchContextCommand(int a, int b, int c, int d);
extern int ReadGlobalPackedBits(int a, int b);
extern Block16 *func_ov002_02066fc8(void);
extern u32 func_ov002_02061930(void);
extern u32 func_ov002_0206193c(void);
extern void CopyWideString(void *dst, u32 value);

void InitPlayerCard(PlayerCard *card)
{
    u32 nameId;

    MI_CpuFill8(card, 0, 0x70);
    OS_GetMacAddress(card->macAddress);
    card->field68 = data_ov015_0207e960[2];
    card->field67 = data_ov015_0207e960[3];
    card->budgetFlag = (u8)DispatchContextCommand(5, 0, 0, 0);
    card->modeFlag = (u8)DispatchContextCommand(6, 0, 0, 0);
    card->field6b = (u8)ReadGlobalPackedBits(0xf38, 4);
    card->header = *func_ov002_02066fc8();
    nameId = func_ov002_02061930();
    CopyWideString(card->ownName, nameId);
    nameId = func_ov002_0206193c();
    CopyWideString(card->otherName, nameId);
}
