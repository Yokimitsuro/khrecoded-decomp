#pragma thumb on

void func_0202d6c8(unsigned int *buf, char *src, unsigned int count) {
    unsigned int i;
    unsigned int n;
    if ((int)count > 0) {
        n = buf[0];
        if (n > count) {
            n = count;
        }
        i = 0;
        if (i < n) {
            do {
                *(unsigned char *)(buf[1] + i) = src[i];
                i++;
            } while (i < n);
        }
        buf[0] = buf[0] - n;
        buf[1] = buf[1] + count;
    }
}
