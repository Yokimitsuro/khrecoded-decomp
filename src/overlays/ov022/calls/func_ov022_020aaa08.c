extern void MIi_CpuCopyFast(const void *src, void *dest, unsigned int size);
extern int data_ov022_020b7e14[];
extern unsigned char data_ov022_020b7828[];

void *func_ov022_020aaa08(void) {
    void *p;

    if (data_ov022_020b7e14[0] == 0) {
        if ((unsigned int)data_ov022_020b7e14[3] >= 0x300) {
            p = (void *)data_ov022_020b7e14[4];
            data_ov022_020b7e14[0] = (int)p;
            MIi_CpuCopyFast(data_ov022_020b7828, p, 0x300);
            data_ov022_020b7e14[4] += 0x300;
            data_ov022_020b7e14[3] -= 0x300;
        } else {
            return data_ov022_020b7828;
        }
    }
    return (void *)data_ov022_020b7e14[0];
}
