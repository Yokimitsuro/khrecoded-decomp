extern void GXS_BeginLoadOBJExtPltt(void);
extern void func_02007f68(void *src, unsigned offset, unsigned size);
extern void func_02007fd0(void);

void func_02013ea0(void *src, unsigned offset, unsigned size) {
    GXS_BeginLoadOBJExtPltt();
    func_02007f68(src, offset, size);
    func_02007fd0();
}
