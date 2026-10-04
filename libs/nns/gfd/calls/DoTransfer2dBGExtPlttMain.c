extern void GX_BeginLoadBGExtPltt(void);
extern void GX_LoadBGExtPltt(void *src, unsigned offset, unsigned size);
extern void GX_EndLoadBGExtPltt(void);

void DoTransfer2dBGExtPlttMain(void *src, unsigned offset, unsigned size) {
    GX_BeginLoadBGExtPltt();
    GX_LoadBGExtPltt(src, offset, size);
    GX_EndLoadBGExtPltt();
}
