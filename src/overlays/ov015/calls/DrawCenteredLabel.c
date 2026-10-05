extern void func_ov002_0206203c(int value);
extern int func_ov002_020621c4(int a, int b);
extern void func_ov002_020627e8(int size[2], int a, int textId);
extern void ActivatePanelSlotAB(int mode, int x, int y, int size, int textId);

void DrawCenteredLabel(void) {
    int size[2];
    int textId;
    func_ov002_0206203c(-1);
    textId = func_ov002_020621c4(0x24, 0);
    func_ov002_020627e8(size, 0, textId);
    textId = func_ov002_020621c4(0x24, 0);
    ActivatePanelSlotAB(0, 0x78 - size[0] / 2, 0x58 - size[1] / 2, 2, textId);
}
