int func_02021c68(unsigned char *a, unsigned char *b, int n) {
    while (n != 0) {
        if (*a++ != *b++) {
            return (a[-1] < b[-1]) ? -1 : 1;
        }
        n--;
    }
    return 0;
}
