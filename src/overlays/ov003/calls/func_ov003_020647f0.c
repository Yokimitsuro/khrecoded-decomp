extern int func_ov003_02063fe4(void);
extern int func_ov022_020a8938(void);

int func_ov003_020647f0(int unused, int frames) {
    int buffered;

    if (func_ov003_02063fe4() == 0) {
        return 1;
    }
    if (frames == 0) {
        return 0;
    }

    buffered = func_ov022_020a8938();
    if (buffered < frames) {
        return 0;
    }
    if (buffered >= frames) {
        return 1;
    }
    return 1;
}
