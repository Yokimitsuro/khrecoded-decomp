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
typedef struct DisplaySessionSettings { int values[6]; } DisplaySessionSettings;
extern const DisplaySessionSettings data_ov026_020b5ab0;
extern const unsigned short data_ov026_020b5af4;
extern int func_02029f6c(void);
extern int func_02029f7c(void);
extern void SetDisplaySetting(int setting);
extern void GXS_LoadBGPltt(const void *source, unsigned offset, unsigned size);
extern void InitializeResourceContainer(OverlayDisplaySession *session, const DisplaySessionSettings *settings);
void InitializeOverlayDisplaySession(OverlayDisplaySession *session, int *alternateUpdate) {
    DisplaySessionSettings settings = data_ov026_020b5ab0;
    session->savedDisplayLayers = (*(volatile unsigned int *)0x04001000 & 0x1f00) >> 8;
    session->savedBrightness = func_02029f6c();
    session->alternateUpdate = *alternateUpdate;
    session->savedDisplaySetting = func_02029f7c();
    session->firstUpdatePending = 1;
    if (func_02029f6c() == 0x10) {
        GXS_LoadBGPltt(&data_ov026_020b5af4, 0, 2);
        session->restorePositiveBrightness = 1;
    }
    SetDisplaySetting(0);
    InitializeResourceContainer(session, &settings);
}
