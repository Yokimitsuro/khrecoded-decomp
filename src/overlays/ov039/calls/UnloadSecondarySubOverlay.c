typedef struct {
    int overlayId;
    void *handler;
} SubOverlayEntry;

extern int data_ov039_020beaa4[2];
extern SubOverlayEntry sOv039_I_020be8ec[];
extern int func_02029f8c(int processor, int overlay_id);

int UnloadSecondarySubOverlay(void)
{
    int result = 1;
    int index = data_ov039_020beaa4[1];

    if (index != -1) {
        result = func_02029f8c(0, sOv039_I_020be8ec[index].overlayId);
        data_ov039_020beaa4[1] = -1;
    }
    return result;
}
