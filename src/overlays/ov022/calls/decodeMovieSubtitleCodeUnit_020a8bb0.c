extern int HandleMovieStreamEvent(int stream, int event);

unsigned short decodeMovieSubtitleCodeUnit_020a8bb0(int stream) {
    int state;
    int *cursor;
    signed char *buf;
    int ch;

    state = *(int *)(stream + 0x60);
    switch (state) {
    case 0:
        cursor = (int *)(stream + 0x58);
        buf = *(signed char **)(stream + 0x68);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        buf = *(signed char **)(stream + (state - 1) * 4 + 0x6c);
        cursor = (int *)(stream + 0x5c);
        break;
    }

    ch = buf[*cursor];
    if (ch == 0) {
        if (state == 0) {
            return 0;
        }
        *(int *)(stream + 0x60) = 0;
        return 1;
    }
    if (ch >= 1 && ch < 0x20) {
        *cursor = *cursor + 1;
        return (unsigned short)HandleMovieStreamEvent(stream, ch);
    }
    if (ch >= 0x20 && ch < 0x80) {
        *cursor = *cursor + 1;
        return (unsigned short)ch;
    }
    if ((ch & 0xe0) == 0xc0) {
        unsigned short cont = (unsigned short)(buf[*cursor + 1] & 0x3f);
        unsigned short v = (unsigned short)(ch & 0x1f);
        unsigned short r = (unsigned short)((v << 6) | cont);
        *cursor = *cursor + 2;
        return r;
    }
    if ((ch & 0xf0) != 0xe0) return;
        unsigned short r = (unsigned short)(((unsigned short)(buf[*cursor + 1] & 0x3f) << 6) | ((unsigned short)(ch & 0xf) << 12) | (unsigned short)(buf[*cursor + 2] & 0x3f));
        *cursor = *cursor + 3;
        return r;

}
