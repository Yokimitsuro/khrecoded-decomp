extern int data_027e00a8;

void func_02019cf4(int *arg0) {
    if (*(int *)&data_027e00a8 == 0) {
        *arg0 = 0;
        *(int *)&data_027e00a8 = (int)arg0;
    }
}
