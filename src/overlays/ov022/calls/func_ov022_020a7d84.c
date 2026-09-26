extern void *G2_GetBG3ScrPtr(void);
void *func_ov022_020a7d84(int direct) {
    if (direct != 0) {
        return (void *)0x6400000;
    }
    return G2_GetBG3ScrPtr();
}
