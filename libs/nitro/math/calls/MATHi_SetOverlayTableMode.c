typedef void (*MATHSHA1ProcessBlockFunc)(void *context);

extern int MATHi_OverlayTableMode;
extern MATHSHA1ProcessBlockFunc MATHi_SHA1ProcessMessageBlockFunc;
extern void MATHi_SHA1ProcessBlockForOverlay(void *context);
extern void MATHi_SHA1ProcessBlock(void *context);

int MATHi_SetOverlayTableMode(int flag)
{
    int previousMode = MATHi_OverlayTableMode;

    MATHi_OverlayTableMode = flag;
    if (flag) {
        MATHi_SHA1ProcessMessageBlockFunc = MATHi_SHA1ProcessBlockForOverlay;
    } else {
        MATHi_SHA1ProcessMessageBlockFunc = MATHi_SHA1ProcessBlock;
    }

    return previousMode;
}