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
extern void updateMovieStreamLeadTime_020a8f1c(MobiClipStream *pStream);

int advanceMovieStreamWindow_020a8a98(MobiClipStream *pStream) {
    int nPosition;
    int nStep;

    nStep = pStream->nBaseStep + GetNestedModeByte(pStream);
    nPosition = (pStream->nWindowPosition += nStep);
    if (nPosition + nStep - pStream->nBaseStep > pStream->nStepLimit) {
        pStream->nWindowPosition -= nStep;
        TextWindow_ScrollUp(pStream, nStep);
    }
    updateMovieStreamLeadTime_020a8f1c(pStream);
    return 1;
}
