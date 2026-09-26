extern void *G2S_GetBG3ScrPtr(void);
void *func_ov022_020a7d9c(int direct) {
    if (direct != 0) {
        return (void *)0x6600000;
    }
    return G2S_GetBG3ScrPtr();
}
