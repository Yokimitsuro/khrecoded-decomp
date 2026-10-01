extern void GX_BeginLoadTexPltt(void);
extern void GX_LoadTexPltt(void *src, unsigned offset, unsigned size);
extern void GX_EndLoadTexPltt(void);

void func_02013e1c(void *src, unsigned offset, unsigned size) {
    GX_BeginLoadTexPltt();
    GX_LoadTexPltt(src, offset, size);
    GX_EndLoadTexPltt();
}
