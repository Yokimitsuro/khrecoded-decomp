extern void MIi_CpuCopyFast(const void *src, void *dest, unsigned int size);
extern int data_ov022_020b7e14[];
extern unsigned char data_ov022_020b76a8[];

void *func_ov022_020aaa78(void) {
    void *p;

    if (data_ov022_020b7e14[8] == 0) {
        if ((unsigned int)data_ov022_020b7e14[3] >= 0x180) {
            p = (void *)data_ov022_020b7e14[4];
            data_ov022_020b7e14[8] = (int)p;
            MIi_CpuCopyFast(data_ov022_020b76a8, p, 0x180);
            data_ov022_020b7e14[4] += 0x180;
            data_ov022_020b7e14[3] -= 0x180;
        } else {
            return data_ov022_020b76a8;
        }
    }
    return (void *)data_ov022_020b7e14[8];
}
