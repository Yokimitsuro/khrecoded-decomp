typedef struct {
    int overlayId;
    void *handler;
} SubOverlayEntry;

extern int data_ov039_020beaa4[2];
extern SubOverlayEntry sOv039_J_020be94c[];
extern int func_02029f8c(int processor, int overlay_id);

int LoadPrimarySubOverlay(int index)
{
    int result = 0;

    data_ov039_020beaa4[0] = index;
    if (index != -1) {
        result = func_02029f8c(0, sOv039_J_020be94c[index].overlayId);
    }
    return result;
}
