typedef struct {
    int overlayId;
    void *handler;
} SubOverlayEntry;

extern int data_ov039_020beaa4[2];
extern SubOverlayEntry sOv039_J_020be94c[];
extern SubOverlayEntry sOv039_I_020be8ec[];
extern void func_02029fac(int processor, int overlay_id);

void UnloadAllSubOverlays(void)
{
    if (data_ov039_020beaa4[0] != -1) {
        func_02029fac(0, sOv039_J_020be94c[data_ov039_020beaa4[0]].overlayId);
        data_ov039_020beaa4[0] = -1;
    }
    if (data_ov039_020beaa4[1] != -1) {
        func_02029fac(0, sOv039_I_020be8ec[data_ov039_020beaa4[1]].overlayId);
        data_ov039_020beaa4[1] = -1;
    }
}
