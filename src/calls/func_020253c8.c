/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
typedef void (*func_02020808_cb)(void);

extern func_02020808_cb ARM9_CTOR_START[];

void func_020253c8(void) {
    func_02020808_cb *callbacks = ARM9_CTOR_START;

    while (callbacks != 0 && *callbacks != 0) {
        (*callbacks)();
        callbacks++;
    }
}
