extern void CpuSet(const void *src, void *dst, unsigned ctrl);
extern int OS_GetLockID(void);

extern int data_0205a2a4;
extern struct { char _pad[6]; unsigned short lockid; } data_0205a2a0;

void CTRDGi_InitCommon(void) {
    int zero = 0;
    CpuSet(&zero, &data_0205a2a4, 0x05000001);
    data_0205a2a0.lockid = (unsigned short)OS_GetLockID();
}
