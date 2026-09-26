extern void FS_WaitAsync(int *file, int a, void *b, int c);
extern int  FS_SeekFile(int file, int pos, int whence);

int func_ov022_020aa188(int cur, int pos, void *b, int c) {
    if (*(unsigned char *)(cur + 0x10) == 1) {
        FS_WaitAsync(*(int **)(cur + 0xc), pos, b, c);
        *(unsigned char *)(cur + 0x10) = 0;
    }
    if (FS_SeekFile(*(int *)(cur + 0xc), pos, 0) == 0) {
        return 0;
    }
    *(int *)(cur + 8) = pos;
    return 1;
}
