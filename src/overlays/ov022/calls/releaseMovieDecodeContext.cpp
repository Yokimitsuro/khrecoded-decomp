typedef unsigned char u8;
typedef unsigned int u32;

class MobiClipReaderRef {
public:
    virtual ~MobiClipReaderRef();
    virtual int Seek(u32 nOffset);
    virtual int Read(void *pDest, u32 nSize);
    virtual int v10();
    virtual int v14();
    virtual void Close();
};

struct MobiClipDecoder {
    MobiClipReaderRef *pReader;
    u8 pad0004[0x34 - 4];
    void *pFrameState;
    u8 pad0038[0x58 - 0x38];
    void *pAudioTracks;
    void **apLuma;
    void **apChroma;
    void **apPlanes;
    void *pScaleLuma;
    void *pScaleChroma;
    void *apScratch[2];
    u8 pad0078[0x94 - 0x78];
    void *pIndex;
    u8 pad0098[0xa8 - 0x98];
    u32 nSlots;
};

extern "C" {

extern void func_ov022_020a7a2c(void *pBlock);

void releaseMovieDecodeContext(MobiClipDecoder *pDecoder)
{
    u32 i;
    int j;

    if (pDecoder->pReader != 0) {
        pDecoder->pReader->Close();
        delete pDecoder->pReader;
    }

    func_ov022_020a7a2c(pDecoder->pFrameState);

    if (pDecoder->apLuma != 0) {
        for (i = 0; i < pDecoder->nSlots; i++) {
            func_ov022_020a7a2c(pDecoder->apLuma[i]);
        }
        func_ov022_020a7a2c(pDecoder->apLuma);
    }
    if (pDecoder->apChroma != 0) {
        for (i = 0; i < pDecoder->nSlots; i++) {
            func_ov022_020a7a2c(pDecoder->apChroma[i]);
        }
        func_ov022_020a7a2c(pDecoder->apChroma);
    }
    if (pDecoder->apPlanes != 0) {
        func_ov022_020a7a2c(pDecoder->apPlanes);
    }
    if (pDecoder->pScaleLuma != 0) {
        func_ov022_020a7a2c(pDecoder->pScaleLuma);
    }
    if (pDecoder->pScaleChroma != 0) {
        func_ov022_020a7a2c(pDecoder->pScaleChroma);
    }
    for (j = 0; j < 2; j++) {
        if (pDecoder->apScratch[j] != 0) {
            func_ov022_020a7a2c(pDecoder->apScratch[j]);
        }
        pDecoder->apScratch[j] = 0;
    }
    if (pDecoder->pIndex != 0) {
        func_ov022_020a7a2c(pDecoder->pIndex);
    }
    if (pDecoder->pAudioTracks != 0) {
        func_ov022_020a7a2c(pDecoder->pAudioTracks);
    }

    pDecoder->pReader = 0;
    pDecoder->apLuma = 0;
    pDecoder->apChroma = 0;
    pDecoder->pScaleLuma = 0;
    pDecoder->pScaleChroma = 0;
    pDecoder->apPlanes = 0;
    pDecoder->pAudioTracks = 0;
    pDecoder->pIndex = 0;
}

}
