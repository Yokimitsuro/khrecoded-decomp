extern void RebindSlotTexture(int a, int b, int c, int d);

void SetSlotKeyAndRebind(int param_1, int param_2, int param_3) {
    *(int *)(param_1 + 0x2c) = param_2;
    RebindSlotTexture(param_1, 0, param_3, 0);
}
