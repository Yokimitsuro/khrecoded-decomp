typedef void (*SubOverlayCallback)(int arg);

typedef struct {
    SubOverlayCallback init;
    SubOverlayCallback exit;
} SubOverlayCallbacks;

typedef struct {
    SubOverlayCallbacks *callbacks;
    int unused;
} SubOverlayHandlerEntry;

typedef struct {
    int overlayId;
    void *handler;
} SubOverlayEntry;

extern int data_ov039_020beaa4[2];
extern SubOverlayHandlerEntry data_ov039_020be8f0[];
extern SubOverlayEntry sOv039_I_020be8ec[];
extern void func_02029fac(int processor, int overlay_id);

void CloseSecondarySubOverlay(int arg)
{
    if (data_ov039_020beaa4[1] == -1) {
        return;
    }
    data_ov039_020be8f0[data_ov039_020beaa4[1]].callbacks->exit(arg);
    func_02029fac(0, sOv039_I_020be8ec[data_ov039_020beaa4[1]].overlayId);
}
