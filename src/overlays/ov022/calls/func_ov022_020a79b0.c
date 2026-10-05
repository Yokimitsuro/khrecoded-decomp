extern int func_ov022_020a73f8(void);
extern int GetSubtitleStreamFrame(void);

int func_ov022_020a79b0(int unused, int frames) {
    int buffered;

    if (func_ov022_020a73f8() == 0) {
        return 1;
    }
    if (frames == 0) {
        return 0;
    }

    buffered = GetSubtitleStreamFrame();
    if (buffered < frames) {
        return 0;
    }
    if (buffered >= frames) {
        return 1;
    }
    return 1;
}
