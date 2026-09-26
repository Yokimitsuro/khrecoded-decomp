extern int *func_01ffb2d4(int a0, int a1, int a2);

int *func_01ffb2f8(int arg0, int arg1, int arg2)
{
    int *p = func_01ffb2d4(arg0, arg1, arg2);
    if (p != 0) {
        int lim;
        p[0] = arg2;
        lim = (int)(*(unsigned short *)(((int *)p[2]) + 1)) << 12;
        if (arg2 >= lim) {
            p[0] = arg2 - lim;
        }
    }
    return p;
}
