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
extern OverlayDisplaySession *data_ov026_020b5b20;
extern void func_ov026_020b5a38(OverlayDisplaySession *session);
void RunOverlayDisplayUpdate(void) {
    OverlayDisplaySession *session = data_ov026_020b5b20;
    if (session == 0) return;
    if (session->updateInProgress != 0) return;
    session->updateInProgress = 1;
    func_ov026_020b5a38(session);
    session->updateInProgress = 0;
}
