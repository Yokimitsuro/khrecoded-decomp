typedef unsigned short u16;
typedef int fx32;

typedef struct NNSG2dSRTControl {
    int type;
    struct {
        fx32 scaleX;
        fx32 scaleY;
        short transX;
        short transY;
        u16 rotZ;
        u16 enableFlag;
    } srtData;
} NNSG2dSRTControl;

static inline void NNSi_G2dSrtcAffineFlagON(NNSG2dSRTControl *control, u16 flag)
{
    control->srtData.enableFlag |= flag;
}

void NNSi_G2dSrtcSetSRTRotZ(NNSG2dSRTControl *control, u16 rotZ)
{
    if (control->type == 1) {
        NNSi_G2dSrtcAffineFlagON(control, 4);
        control->srtData.rotZ = rotZ;
    }
}
