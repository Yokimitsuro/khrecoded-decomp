typedef struct {
    unsigned char unknown_0000[0xc9c4];
    int unknown_c9c4;
} OverlayEventStatePrefix;
extern OverlayEventStatePrefix *data_ov039_020bea20;
int GetStateC9C4(void) { return data_ov039_020bea20->unknown_c9c4; }
