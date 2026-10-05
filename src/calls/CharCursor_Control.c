typedef struct {
    unsigned char *pos;
    int eof;
} CharCursor;

int CharCursor_Control(CharCursor *s, int c, int cmd) {
    switch (cmd) {
    case 0: {
        unsigned char *p = s->pos;
        int ch = *p;
        if (ch == 0) {
            s->eof = 1;
            return -1;
        }
        s->pos = p + 1;
        return ch;
    }
    case 1:
        if (s->eof == 0) {
            s->pos = s->pos - 1;
        } else {
            s->eof = 0;
        }
        return c;
    case 2:
        return s->eof;
    default:
        return 0;
    }
}
