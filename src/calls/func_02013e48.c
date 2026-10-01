extern void GX_BeginLoadOBJExtPltt(void);
extern void func_02007dec(void *src, unsigned offset, unsigned size);
extern void func_02007e5c(void);

void func_02013e48(void *src, unsigned offset, unsigned size) {
    GX_BeginLoadOBJExtPltt();
    func_02007dec(src, offset, size);
    func_02007e5c();
}
