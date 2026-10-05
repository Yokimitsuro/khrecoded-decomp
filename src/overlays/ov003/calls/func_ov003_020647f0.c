extern int MovieScene_IsAnyStateTwo(void);
extern int GetSubtitleStreamFrame(void);

int func_ov003_020647f0(int unused, int frames) {
    int buffered;

    if (MovieScene_IsAnyStateTwo() == 0) {
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
