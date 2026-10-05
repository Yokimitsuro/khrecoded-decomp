void CTRDGi_ChangeLatestAccessCycle(int *saved) {
    volatile unsigned short *exmemcnt = (volatile unsigned short *)0x4000204;
    saved[0] = (*exmemcnt & 0xc) >> 2;
    saved[1] = (*exmemcnt & 0x10) >> 4;
    *exmemcnt = (unsigned short)((*exmemcnt & ~0xc) | 0xc);
    *exmemcnt = (unsigned short)(*exmemcnt & ~0x10);
}
