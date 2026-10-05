typedef struct OverlayObject OverlayObject;
extern void *NNSi_FndAllocFromDefaultHeap(unsigned int size);
extern void func_ov021_020a75c4(OverlayObject *object, int variant, int selectionIndex);
OverlayObject *CreateOverlay060Object(void)
{
    OverlayObject *object = NNSi_FndAllocFromDefaultHeap(0x230);
    func_ov021_020a75c4(object, 1, 0);
    return object;
}
