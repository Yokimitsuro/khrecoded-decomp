#include "nitro/types.h"

extern u8 *data_ov002_0206c464;

extern void func_ov002_020620fc(int arg);
extern int func_ov002_020621c4(int textIndex, int unused);
extern void func_ov002_020627e8(int size[2], int mode, int textId);
extern void ActivatePanelSlotCD(int mode, int x, int y, int size, int textId);
extern int func_ov027_020ba2c8(void *messages, int index);

void ShowSaveMessage(int mode)
{
    int size[2];
    int choiceSize[2];
    int altChoiceSize[2];

    func_ov002_020620fc(0);
    switch (mode) {
    case 0:
        func_ov002_020627e8(size, 0, func_ov002_020621c4(0x14, 0));
        ActivatePanelSlotCD(0, 0x78 - size[0] / 2, 0x60 - size[1] / 2, 2, func_ov002_020621c4(0x14, 0));
        break;
    case 1:
        ActivatePanelSlotCD(0, 0x23, 0x52, 2, func_ov002_020621c4(0x15, 0));
        func_ov002_020627e8(choiceSize, 0, func_ov002_020621c4(0x3c, 0));
        ActivatePanelSlotCD(0, 0x46 - choiceSize[0] / 2, 99, 2, func_ov002_020621c4(0x3c, 0));
        func_ov002_020627e8(choiceSize, 0, func_ov002_020621c4(0x3d, 0));
        ActivatePanelSlotCD(0, 0xa5 - choiceSize[0] / 2, 99, 2, func_ov002_020621c4(0x3d, 0));
        break;
    case 2:
        func_ov002_020627e8(size, 0, func_ov027_020ba2c8(data_ov002_0206c464 + 0xce64, 0xf));
        ActivatePanelSlotCD(0, 0x78 - size[0] / 2, 0x60 - size[1] / 2, 2, func_ov027_020ba2c8(data_ov002_0206c464 + 0xce64, 0xf));
        break;
    case 3:
        ActivatePanelSlotCD(0, 0x23, 0x52, 2, func_ov002_020621c4(0x73, 0));
        func_ov002_020627e8(altChoiceSize, 0, func_ov002_020621c4(0x3c, 0));
        ActivatePanelSlotCD(0, 0x46 - altChoiceSize[0] / 2, 99, 2, func_ov002_020621c4(0x3c, 0));
        func_ov002_020627e8(altChoiceSize, 0, func_ov002_020621c4(0x3d, 0));
        ActivatePanelSlotCD(0, 0xa5 - altChoiceSize[0] / 2, 99, 2, func_ov002_020621c4(0x3d, 0));
        break;
    case 4:
        func_ov002_020627e8(size, 0, func_ov027_020ba2c8(data_ov002_0206c464 + 0xce64, 0xd));
        ActivatePanelSlotCD(0, 0x78 - size[0] / 2, 0x60 - size[1] / 2, 2, func_ov027_020ba2c8(data_ov002_0206c464 + 0xce64, 0xd));
        break;
    }
}
