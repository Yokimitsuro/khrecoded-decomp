extern void func_02007da4(void);
extern void func_02007dec(void *src, unsigned offset, unsigned size);
extern void func_02007e5c(void);

void func_02013e48(void *src, unsigned offset, unsigned size) {
    func_02007da4();
    func_02007dec(src, offset, size);
    func_02007e5c();
}
