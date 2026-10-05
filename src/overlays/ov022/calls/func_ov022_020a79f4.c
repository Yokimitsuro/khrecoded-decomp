extern int IsMoviePlaybackIdle();
int func_ov022_020a79f4(void) {
    if (IsMoviePlaybackIdle() != 0) return 1;
    return 0;
}
