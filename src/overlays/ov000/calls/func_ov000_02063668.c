extern int data_ov000_02063a04;

void func_ov000_02063668(int arg0) {
    int p = *(int *)&data_ov000_02063a04;
    if (p != 0) {
        *(int *)(p + 4) = arg0;
    }
}
