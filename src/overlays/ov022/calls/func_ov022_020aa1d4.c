extern void FS_WaitAsync(int file);
extern int  FS_SeekFile(int file, int pos, int whence);
extern int  FS_ReadFile(int file, void *dst, unsigned int len);

int func_ov022_020aa1d4(int cur, void *dst, unsigned int len) {
    if (*(unsigned char *)(cur + 0x10) == 1) {
        FS_WaitAsync(*(int *)(cur + 0xc));
        FS_SeekFile(*(int *)(cur + 0xc), *(int *)(cur + 8), 0);
        *(unsigned char *)(cur + 0x10) = 0;
    }
    if (FS_ReadFile(*(int *)(cur + 0xc), dst, len) == -1) {
        return 0;
    }
    *(int *)(cur + 8) += len;
    return 1;
}
