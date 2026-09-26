extern void *func_02025d1c(void *arg);

int func_02025df8(void *arg) {
    short *p = (short *)func_02025d1c(arg);
    int r = 0;
    if (*p == 1) r = ((int *)p)[1];
    return r;
}
