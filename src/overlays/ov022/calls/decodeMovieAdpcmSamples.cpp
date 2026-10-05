typedef unsigned char u8;
typedef signed char s8;
typedef short s16;
typedef unsigned short u16;
typedef unsigned int u32;

#define INDEX_MAX   0x58
#define SAMPLE_MIN  (-0x8000)
#define SAMPLE_MAX  0x7fff

struct MobiClipAdpcmState {
    int nSample;
    int nIndex;
};

extern "C" {

extern const s16 data_ov022_020b7b38[];
extern const s8 data_ov022_020b7b28[];

void decodeMovieAdpcmSamples(MobiClipAdpcmState *pState, const u8 *pSrc, int nCount,
                         u32 *pDst)
{
    int i;
    int nCode;
    int nPrev;
    int nDiff;
    int nFirst;
    int nStep;

    for (i = 0; i < nCount; i++) {
        nCode = pSrc[i];

        nPrev = pState->nIndex;
        nStep = data_ov022_020b7b38[nPrev];
        pState->nIndex = pState->nIndex + data_ov022_020b7b28[nCode & 7];
        if (pState->nIndex < 0) {
            pState->nIndex = 0;
        }
        if (pState->nIndex > INDEX_MAX) {
            pState->nIndex = INDEX_MAX;
        }
        nDiff = nStep >> 3;
        if (nCode & 4) {
            nDiff += nStep;
        }
        if (nCode & 2) {
            nDiff += nStep >> 1;
        }
        if (nCode & 1) {
            nDiff += nStep >> 2;
        }
        if (nCode & 8) {
            pState->nSample = pState->nSample - nDiff;
        } else {
            pState->nSample = pState->nSample + nDiff;
        }
        nCode = nCode >> 4;
        if (pState->nSample < SAMPLE_MIN) {
            pState->nSample = SAMPLE_MIN;
        }
        if (pState->nSample > SAMPLE_MAX) {
            pState->nSample = SAMPLE_MAX;
        }

        nFirst = pState->nSample;
        nPrev = pState->nIndex;
        nStep = data_ov022_020b7b38[nPrev];
        pState->nIndex = pState->nIndex + data_ov022_020b7b28[nCode & 7];
        if (pState->nIndex < 0) {
            pState->nIndex = 0;
        }
        if (pState->nIndex > INDEX_MAX) {
            pState->nIndex = INDEX_MAX;
        }
        nDiff = nStep >> 3;
        if (nCode & 4) {
            nDiff += nStep;
        }
        if (nCode & 2) {
            nDiff += nStep >> 1;
        }
        if (nCode & 1) {
            nDiff += nStep >> 2;
        }
        if (nCode & 8) {
            pState->nSample = pState->nSample - nDiff;
        } else {
            pState->nSample = pState->nSample + nDiff;
        }
        if (pState->nSample < SAMPLE_MIN) {
            pState->nSample = SAMPLE_MIN;
        }
        if (pState->nSample > SAMPLE_MAX) {
            pState->nSample = SAMPLE_MAX;
        }

        *pDst++ = (u32)(pState->nSample * 0x10000) | (u32)(u16)nFirst;
    }
}

}
