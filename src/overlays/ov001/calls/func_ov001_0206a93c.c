extern int RebindSlotTexture();

int func_ov001_0206a93c(int arg0, int arg1) {
    *(int *)(arg0 + 0x2c) = arg1;
    RebindSlotTexture(arg0, 0);
    return 1;
}
