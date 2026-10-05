extern int data_ov039_020bea20;
extern void func_ov039_020bcf40(int arg0);
extern void CloseSecondarySubOverlay(int arg0);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void LoadBgLayerSet4(void);
extern void UnloadSecondarySubOverlay(void);
extern void RuntimeState_SetMode(int value);

void CleanupHandlersAndSetPhase5(void)
{
    int base = data_ov039_020bea20;

    func_ov039_020bcf40(*(int *)(base + 0xc998));
    CloseSecondarySubOverlay(*(int *)(base + 0xc99c));
    if (*(int *)(base + 0xc99c) != 0) {
        NNSi_FndFreeFromDefaultHeap((void *)*(int *)(base + 0xc99c));
        *(int *)(base + 0xc99c) = 0;
    }
    *(int *)(base + 0xca30) = 0;
    LoadBgLayerSet4();
    UnloadSecondarySubOverlay();
    RuntimeState_SetMode(5);
}
