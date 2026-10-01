extern void *G2S_GetBG2ScrPtr(void);
extern void MI_CpuClear32_0x800(void *destination);

void G2S_ClearBG2Screen(void) {
    MI_CpuClear32_0x800(G2S_GetBG2ScrPtr());
}
