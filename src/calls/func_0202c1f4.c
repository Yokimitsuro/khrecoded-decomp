extern void GX_BeginLoadTexPltt(void);
extern void func_02008228(void *src, unsigned offset, unsigned size);
extern void func_02008298(void);

void func_0202c1f4(void *src, unsigned offset, unsigned size) {
    GX_BeginLoadTexPltt();
    func_02008228(src, offset, size);
    func_02008298();
}
