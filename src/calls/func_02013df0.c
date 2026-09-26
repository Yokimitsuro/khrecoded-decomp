extern void GX_BeginLoadTex(void);
extern void func_02008064(void *src, unsigned offset, unsigned size);
extern void func_020081b0(void);

void func_02013df0(void *src, unsigned offset, unsigned size) {
    GX_BeginLoadTex();
    func_02008064(src, offset, size);
    func_020081b0();
}
