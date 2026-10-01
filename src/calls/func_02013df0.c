extern void GX_BeginLoadTex(void);
extern void GX_LoadTex(void *src, unsigned offset, unsigned size);
extern void GX_EndLoadTex(void);

void func_02013df0(void *src, unsigned offset, unsigned size) {
    GX_BeginLoadTex();
    GX_LoadTex(src, offset, size);
    GX_EndLoadTex();
}
