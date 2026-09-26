typedef unsigned short u16;

extern int strncmp(const char *a, const char *b, int n);

char *func_ov001_020670b4(char *self, const char *name, int length, int *pIndex) {
    if (*pIndex < *(u16 *)(self + 0x82)) {
        do {
            long offset = *pIndex * 0x14;
            char *table = *(char **)(self + 0xac);

            if (strncmp(table + offset, name, length) == 0) {
                return table + offset;
            }
            *pIndex = *pIndex + 1;
        } while (*pIndex < *(u16 *)(self + 0x82));
    }
    return 0;
}
