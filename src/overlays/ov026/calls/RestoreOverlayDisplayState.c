typedef struct OverlayDisplaySession {
    unsigned char sharedState[0x647c];
    int alternateUpdate;
    int firstUpdatePending;
    int restorePositiveBrightness;
    unsigned int savedDisplayLayers;
    int savedBrightness;
    int savedDisplaySetting;
    int updateInProgress;
    void *updateRegistration;
} OverlayDisplaySession;
extern void func_ov027_020b8c78(OverlayDisplaySession *session);
extern void OS_WaitVBlankIntr(void);
extern void SetSecondaryBrightness(int brightness);
extern void SetDisplaySetting(int setting);
void RestoreOverlayDisplayState(OverlayDisplaySession *session) {
    int brightness = -16;
    func_ov027_020b8c78(session);
    if (session->restorePositiveBrightness) brightness = 16;
    OS_WaitVBlankIntr();
    SetSecondaryBrightness(brightness);
    *(volatile unsigned int *)0x04001000 = (*(volatile unsigned int *)0x04001000 & ~0x1f00) | (session->savedDisplayLayers << 8);
    SetDisplaySetting(session->savedDisplaySetting);
}
