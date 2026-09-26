extern void FS_WaitAsync(int *file);

void func_ov022_020aa2c0(int cur) {
    if (*(unsigned char *)(cur + 0x10) == 1) {
        FS_WaitAsync(*(int **)(cur + 0xc));
    }
    *(unsigned char *)(cur + 0x10) = 0;
}
