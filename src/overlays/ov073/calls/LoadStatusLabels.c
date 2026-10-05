#include "nitro/types.h"

typedef struct StringTable {
    void *buffer;
    u32 count;
    u8 *entries;
} StringTable;

typedef struct StatusMenu {
    u8 pad_000[0x2c];
    u16 *statLabels[9];
    u16 valueTextA[2][4];
    u16 valueTextB[2][10];
    u16 valueTextC[2][4];
    u16 valueTextD[2][4];
    u16 valueTextE[2][4];
    u16 valueTextF[2][4];
    u16 *statValues[8][2];
    u16 valueTextG[9];
    u16 valueTextH[9];
    u8 pad_12c[0xa5c - 0x12c];
    u16 *sectionTitle;
    u16 *sectionLabels[7];
    u16 *columnHeaders[4];
    u16 columnText[7][8];
    u16 *columnLines[8];
    u16 *detailLabels[8];
    u8 pad_b3c[0x11cc - 0xb3c];
    StringTable strings;
} StatusMenu;

extern u16 *func_ov027_020ba2c8(StringTable *table, int index);

void LoadStatusLabels(StatusMenu *menu)
{
    menu->statLabels[0] = func_ov027_020ba2c8(&menu->strings, 6);
    menu->statLabels[1] = func_ov027_020ba2c8(&menu->strings, 7);
    menu->statLabels[2] = func_ov027_020ba2c8(&menu->strings, 8);
    menu->statLabels[3] = func_ov027_020ba2c8(&menu->strings, 9);
    menu->statLabels[4] = func_ov027_020ba2c8(&menu->strings, 0xb);
    menu->statLabels[5] = func_ov027_020ba2c8(&menu->strings, 0xa);
    menu->statLabels[6] = func_ov027_020ba2c8(&menu->strings, 0xc);
    menu->statLabels[7] = func_ov027_020ba2c8(&menu->strings, 0xd);
    menu->statLabels[8] = func_ov027_020ba2c8(&menu->strings, 0xe);

    menu->statValues[0][0] = menu->valueTextA[0];
    menu->statValues[1][0] = menu->valueTextB[0];
    menu->statValues[2][0] = menu->valueTextC[0];
    menu->statValues[3][0] = menu->valueTextE[0];
    menu->statValues[4][0] = menu->valueTextD[0];
    menu->statValues[5][0] = menu->valueTextF[0];
    menu->statValues[6][0] = menu->valueTextG;
    menu->statValues[7][0] = menu->valueTextH;
    menu->statValues[0][1] = menu->valueTextA[1];
    menu->statValues[1][1] = menu->valueTextB[1];
    menu->statValues[2][1] = menu->valueTextC[1];
    menu->statValues[3][1] = menu->valueTextE[1];
    menu->statValues[4][1] = menu->valueTextD[1];
    menu->statValues[5][1] = menu->valueTextF[1];
    menu->statValues[6][1] = menu->valueTextG;
    menu->statValues[7][1] = menu->valueTextH;

    menu->sectionTitle = func_ov027_020ba2c8(&menu->strings, 0xf);
    menu->sectionLabels[0] = func_ov027_020ba2c8(&menu->strings, 0x14);
    menu->sectionLabels[1] = func_ov027_020ba2c8(&menu->strings, 0x15);
    menu->sectionLabels[2] = func_ov027_020ba2c8(&menu->strings, 0x16);
    menu->sectionLabels[3] = func_ov027_020ba2c8(&menu->strings, 0x17);
    menu->sectionLabels[4] = func_ov027_020ba2c8(&menu->strings, 0x18);
    menu->sectionLabels[5] = func_ov027_020ba2c8(&menu->strings, 0x19);
    menu->sectionLabels[6] = func_ov027_020ba2c8(&menu->strings, 0x1a);
    menu->columnHeaders[0] = func_ov027_020ba2c8(&menu->strings, 0x10);
    menu->columnHeaders[1] = func_ov027_020ba2c8(&menu->strings, 0x11);
    menu->columnHeaders[2] = func_ov027_020ba2c8(&menu->strings, 0x12);
    menu->columnHeaders[3] = func_ov027_020ba2c8(&menu->strings, 0x13);

    menu->columnLines[0] = menu->columnHeaders[0];
    menu->columnLines[1] = menu->columnText[0];
    menu->columnLines[2] = menu->columnText[1];
    menu->columnLines[3] = menu->columnText[2];
    menu->columnLines[4] = menu->columnText[3];
    menu->columnLines[5] = menu->columnText[4];
    menu->columnLines[6] = menu->columnText[5];
    menu->columnLines[7] = menu->columnText[6];

    menu->detailLabels[0] = func_ov027_020ba2c8(&menu->strings, 0x1b);
    menu->detailLabels[1] = func_ov027_020ba2c8(&menu->strings, 0x1c);
    menu->detailLabels[2] = func_ov027_020ba2c8(&menu->strings, 0x1d);
    menu->detailLabels[3] = func_ov027_020ba2c8(&menu->strings, 0x1e);
    menu->detailLabels[4] = func_ov027_020ba2c8(&menu->strings, 0x1f);
    menu->detailLabels[5] = func_ov027_020ba2c8(&menu->strings, 0x20);
    menu->detailLabels[6] = func_ov027_020ba2c8(&menu->strings, 0x21);
    menu->detailLabels[7] = func_ov027_020ba2c8(&menu->strings, 0x22);
}
