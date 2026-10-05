typedef unsigned char u8;

typedef struct MobiClipStream {
    u8 _pad00[0x38];
    int nStepLimit;
    u8 _pad48[0x0c];
    int nBaseStep;
    u8 _pad58[0x04];
    int nWindowPosition;
} MobiClipStream;

extern u8 GetNestedModeByte(MobiClipStream *pStream);
extern void TextWindow_ScrollUp(MobiClipStream *pStream, int nStep);
extern void func_ov003_02064e2c(MobiClipStream *pStream);

int advanceMovieStreamWindow(MobiClipStream *pStream) {
    int nPosition;
    int nStep;

    nStep = pStream->nBaseStep + GetNestedModeByte(pStream);
    nPosition = (pStream->nWindowPosition += nStep);
    if (nPosition + nStep - pStream->nBaseStep > pStream->nStepLimit) {
        pStream->nWindowPosition -= nStep;
        TextWindow_ScrollUp(pStream, nStep);
    }
    func_ov003_02064e2c(pStream);
    return 1;
}
