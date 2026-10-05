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
extern void GXS_LoadBGPltt(const void *source, unsigned offset, unsigned size);
extern void InitializeOverlayDisplaySession(OverlayDisplaySession *session, int *alternateUpdate);
extern void SetPanelSessionActive(void);
extern void *AddFieldListener(void (*callback)(void));
extern void RunOverlayDisplayUpdate(void);
extern int ShouldRestorePositiveBrightness(OverlayDisplaySession *session);
extern void RequestPanelBrightnessRestore(void);
extern int func_ov026_020b58e8(void);
int (*BeginOverlayDisplaySession(void))(void) {
    OverlayDisplaySession *session = NNSi_FndGetCurrentRootHeap();
    unsigned short paletteValue = 0;
    int alternateUpdate;
    data_ov026_020b5b20 = session;
    alternateUpdate = 1;
    GXS_LoadBGPltt(&paletteValue, 0, 2);
    InitializeOverlayDisplaySession(session, &alternateUpdate);
    SetPanelSessionActive();
    session->updateRegistration = AddFieldListener(RunOverlayDisplayUpdate);
    if (ShouldRestorePositiveBrightness(session)) RequestPanelBrightnessRestore();
    return func_ov026_020b58e8;
}
