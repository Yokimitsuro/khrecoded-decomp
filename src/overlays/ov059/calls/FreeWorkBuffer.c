extern void Actor_ReleaseResources();
extern int data_ov059_020cffc0;

void FreeWorkBuffer(void) {
    int p = *(int *)&data_ov059_020cffc0;
    if (p == 0) {
        return;
    }
    Actor_ReleaseResources(p);
    data_ov059_020cffc0 = 0;
}
