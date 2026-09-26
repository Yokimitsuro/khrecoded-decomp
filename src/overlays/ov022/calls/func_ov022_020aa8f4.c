extern int data_ov022_020b7e14[];

void func_ov022_020aa8f4(int base, unsigned int size) {
    data_ov022_020b7e14[4] = base;
    data_ov022_020b7e14[3] = size & 0xfffffffc;
    data_ov022_020b7e14[1] = 0;
    data_ov022_020b7e14[0] = 0;
    data_ov022_020b7e14[8] = 0;
}
