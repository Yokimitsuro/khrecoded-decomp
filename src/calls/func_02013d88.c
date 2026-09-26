extern int data_0205a8c4;

void func_02013d88(void) {
    *(int *)&data_0205a8c4 = 0;
    *(int *)((char *)&data_0205a8c4 + 4) = *(int *)((char *)&data_0205a8c4 + 8);
}
