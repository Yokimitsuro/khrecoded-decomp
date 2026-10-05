extern void func_ov059_020cbd08();
extern int data_ov059_020cffc0;

void FreeWorkBuffer(void) {
    int p = *(int *)&data_ov059_020cffc0;
    if (p == 0) {
        return;
    }
    func_ov059_020cbd08(p);
    data_ov059_020cffc0 = 0;
}
