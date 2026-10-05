typedef unsigned int u32;

struct MobiClipReaderRaw {
    const void *pVtable;
    u32 fileSize;
    u32 filePosition;
    void *fileContext;
    u32 stateWord;
};

class MobiClipReader {
public:
    virtual ~MobiClipReader();
};

extern "C" {

extern int gStreamStateHandlers;
extern int gStreamIoCallbacks;

extern void *func_ov022_020aa138(u32 nSize);
extern void *func_ov022_020a93f4(u32 nSize);
extern void func_ov022_020a9400(void *pBlock);
extern int func_ov022_020aa150(void *pReader, void *pFile);
extern void *func_ov022_020a940c(void *pBlock);
extern int initializeMovieStreamWrapper(void *pStream, void *pReader, int slotCount);
extern void func_ov022_020a943c(void *pStream);

void *createMovieStream(void *pFile, int slotCount)
{
    MobiClipReaderRaw *pReader;
    void *pStream;

    pReader = (MobiClipReaderRaw *)func_ov022_020aa138(0x14);
    if (pReader != 0) {
        pReader->pVtable = &gStreamStateHandlers;
        pReader->fileSize = 0;
        pReader->filePosition = 0;
        pReader->pVtable = &gStreamIoCallbacks;
    }
    if (pReader == 0) {
        return 0;
    }

    if (func_ov022_020aa150(pReader, pFile) == 0) {
        delete (MobiClipReader *)pReader;
        return 0;
    }

    pStream = func_ov022_020a93f4(0xd8);
    if (pStream != 0) {
        pStream = func_ov022_020a940c(pStream);
    }
    if (initializeMovieStreamWrapper(pStream, pReader, slotCount) == 0) {
        if (pStream != 0) {
            func_ov022_020a943c(pStream);
            func_ov022_020a9400(pStream);
        }
        return 0;
    }
    return pStream;
}

}
