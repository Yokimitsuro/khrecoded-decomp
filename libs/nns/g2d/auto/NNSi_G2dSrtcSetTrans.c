typedef short s16;
typedef unsigned short u16;
typedef int fx32;

typedef struct NNSG2dSRTControl {
    int type;
    struct {
        fx32 scaleX;
        fx32 scaleY;
        s16 transX;
        s16 transY;
        u16 rotZ;
        u16 enableFlag;
    } srtData;
} NNSG2dSRTControl;

static inline void NNSi_G2dSrtcAffineFlagON(NNSG2dSRTControl *control, u16 flag)
{
    control->srtData.enableFlag |= flag;
}

void NNSi_G2dSrtcSetTrans(NNSG2dSRTControl *control, s16 x, s16 y)
{
    if (control->type == 1) {
        NNSi_G2dSrtcAffineFlagON(control, 8);
        control->srtData.transX = x;
        control->srtData.transY = y;
    }
}
