extern int *func_01ffb2d4();

int Anim_GetFrame(unsigned short *r0, int r1) {
    int *p = func_01ffb2d4(r0, r1);
    if (p == 0) return 0;
    return *p;
}
