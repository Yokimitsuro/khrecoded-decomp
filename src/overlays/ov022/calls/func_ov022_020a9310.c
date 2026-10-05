extern int queueNextMovieFrame(int arg);
int func_ov022_020a9310(int param_1) {
    if (param_1 == 0) return 0;
    return queueNextMovieFrame(param_1) == 1;
}
