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
extern OverlayDisplaySession *NNSi_FndGetCurrentRootHeap(void);
extern void FreeSceneListObject(void *registration);
extern void RestoreOverlayDisplayState(OverlayDisplaySession *session);
void EndOverlayDisplaySession(void) {
    OverlayDisplaySession *session = NNSi_FndGetCurrentRootHeap();
    FreeSceneListObject(session->updateRegistration);
    RestoreOverlayDisplayState(session);
    data_ov026_020b5b20 = 0;
}
