typedef struct {
    int overlayId;
    void *handler;
} SubOverlayEntry;

extern int data_ov039_020beaa4[2];
extern SubOverlayEntry sOv039_J_020be94c[];
extern int func_02029fac(int processor, int overlay_id);

int UnloadPrimarySubOverlay(void)
{
    int result = 1;
    int index = data_ov039_020beaa4[0];

    if (index != -1) {
        result = func_02029fac(0, sOv039_J_020be94c[index].overlayId);
        data_ov039_020beaa4[0] = -1;
    }
    return result;
}
