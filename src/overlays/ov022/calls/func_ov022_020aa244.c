extern int FS_SeekFile(int file, int pos, int whence);
extern int FS_ReadFileAsync(int file, void *dst, unsigned int len);

int func_ov022_020aa244(int cur, void *dst, unsigned int len) {
    int pos = *(int *)(cur + 8);
    int base = pos & -0x200;
    int skew = pos - base;
    unsigned int total = len + skew;

    if (total & 0x1ff) {
        total = (total & -0x200) + 0x200;
    }
    FS_SeekFile(*(int *)(cur + 0xc), base, 0);
    if (FS_ReadFileAsync(*(int *)(cur + 0xc), dst, total) == -1) {
        return 0;
    }
    *(int *)(cur + 8) += len;
    *(unsigned char *)(cur + 0x10) = 1;
    return skew;
}
