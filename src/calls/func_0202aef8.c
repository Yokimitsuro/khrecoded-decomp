extern unsigned short data_02055580[];

int func_0202aef8(int param_1) {
    unsigned short regOff = data_02055580[param_1];
    if (regOff == 0) return param_1;
    {
        volatile unsigned short *reg = (volatile unsigned short *)(regOff + 0x04000000);
        if (*reg & 0x2000) return param_1 + 2;
    }
    return param_1;
}
