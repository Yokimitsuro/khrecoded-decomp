/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern char gFileLoader[];
extern void EnqueueGfxCmd0();
extern void EnqueueGfxCmd1();
extern void func_0202c1b0();
extern void func_0202c1f4();

void func_0202c6a4(int arg0) {
    if (arg0 == 0) {
        *(void **)(gFileLoader + 0xc) = (void *)func_0202c1b0;
        *(void **)(gFileLoader + 0x10) = (void *)func_0202c1f4;
    } else {
        *(void **)(gFileLoader + 0xc) = (void *)EnqueueGfxCmd0;
        *(void **)(gFileLoader + 0x10) = (void *)EnqueueGfxCmd1;
    }
}
