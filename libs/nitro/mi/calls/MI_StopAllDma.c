typedef unsigned int u32;

extern void MI_StopDma(u32 dmaNo);

void MI_StopAllDma(void)
{
    MI_StopDma(0);
    MI_StopDma(1);
    MI_StopDma(2);
    MI_StopDma(3);
}