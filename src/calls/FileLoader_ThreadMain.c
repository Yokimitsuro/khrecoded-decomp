#include "nitro/types.h"

typedef struct OSThreadQueue {
    struct OSThread *head;
    struct OSThread *tail;
} OSThreadQueue;

typedef struct LoaderRequest {
    struct LoaderRequest *next;
    int type;
    union {
        struct {
            void *archive;
            u32 imageTop;
            u32 imageBottom;
        } file;
        struct {
            u16 dataId;
            u16 waveId;
            void *heap;
            u8 *statusOut;
        } snd;
    } u;
    u8 uncompressContext[0x28 - 0x14];
    u8 *dest;
    u32 size;
} LoaderRequest;

typedef struct LoaderBlockFlags {
    u8 cur : 1;
    u8 prev : 1;
    u8 first : 1;
} LoaderBlockFlags;

typedef struct LoaderReader {
    u8 block[2][0x200];
    u8 file[0x48];
    LoaderRequest *request;
    OSThreadQueue idleQueue;
    int blockLen[2];
    LoaderBlockFlags flags;
} LoaderReader;

typedef struct FileLoader {
    void *reader;
    LoaderReader *reader2;
    u8 pad_08[0x3c - 0x8];
    int hold;
} FileLoader;

extern FileLoader gFileLoader;
extern u8 data_02060584[];

extern void OS_WakeupThread(OSThreadQueue *queue);
extern BOOL OS_ReceiveMessage(void *queue, void *msg, int flags);
extern BOOL FS_OpenFileDirect(void *file, void *archive, u32 imageTop, u32 imageBottom, u32 fileIndex);
extern void FSi_WaitForCardThread(void);
extern int FS_ReadFile(void *file, void *dst, int len);
extern int FS_ReadFileAsync(void *file, void *dst, int len);
extern void OS_Terminate(void);
extern int MI_ReadUncompLZ8(void *context, void *src, int len);
extern void FS_WaitAsync(void *file);
extern void FS_CloseFile(void *file);
extern void DC_FlushAll(void);
extern void DC_FlushRange(void *buffer, u32 size);
extern void OS_RescheduleThread(void);
extern void NNS_SndArcLoadSeq(u32 dataId, void *heap);
extern BOOL NNS_SndArcLoadSeqArc(u32 dataId, void *heap);
extern BOOL NNS_SndArcLoadBank(u32 waveId, void *heap);
extern void *GetSoundStreamHandle(u32 dataId);
extern BOOL NNS_SndArcStrmPrepare(void *handle, u32 waveId, int flags);
extern void func_0202b880(LoaderRequest *request);

static inline void FlushLoaded(void *buffer, u32 size)
{
    if (size >= 0x2400) {
        DC_FlushAll();
    } else {
        DC_FlushRange(buffer, size);
    }
}

void FileLoader_ThreadMain(void *arg)
{
    int state = 0;
    LoaderRequest *request;
    LoaderReader *reader = gFileLoader.reader2;

    for (;;) {
        switch (state) {
        case 0:
            if (gFileLoader.hold == 0) {
                OS_WakeupThread(&reader->idleQueue);
                reader->request = 0;
            }
            OS_ReceiveMessage(data_02060584, &reader->request, 1);
            if (reader->request == 0) {
                return;
            }
            reader->blockLen[1] = 0;
            reader->blockLen[0] = 0;
            request = reader->request;
            switch (request->type) {
            case 0:
                FS_OpenFileDirect(reader->file, request->u.file.archive, request->u.file.imageTop, request->u.file.imageBottom, 0);
                state = 4;
                break;
            case 1:
                FS_OpenFileDirect(reader->file, request->u.file.archive, request->u.file.imageTop, request->u.file.imageBottom, 0);
                state = 2;
                break;
            case 2:
                state = 5;
                break;
            case 3:
                state = 6;
                break;
            case 4:
                state = 7;
                break;
            }
            break;
        case 2:
            reader->flags.cur = 0;
            reader->flags.prev = 1;
            reader->flags.first = 1;
            FSi_WaitForCardThread();
            reader->blockLen[reader->flags.cur] = FS_ReadFile(reader->file, reader->block[reader->flags.cur], 0x200);
            state = 3;
            break;
        case 3:
            reader->flags.cur ^= 1;
            reader->flags.prev ^= 1;
            FSi_WaitForCardThread();
            reader->blockLen[reader->flags.cur] = FS_ReadFileAsync(reader->file, reader->block[reader->flags.cur], 0x200);
            if (reader->blockLen[reader->flags.prev] == 0) {
                break;
            }
            if (reader->blockLen[reader->flags.prev] == -1) {
                OS_Terminate();
            }
            {
                u8 *src = reader->block[reader->flags.prev];
                int len = reader->blockLen[reader->flags.prev];

                if (reader->flags.first) {
                    src += 4;
                    len -= 4;
                    reader->flags.first = 0;
                }
                if (MI_ReadUncompLZ8(request->uncompressContext, src, len) == 0) {
                    FS_WaitAsync(reader->file);
                    FS_CloseFile(reader->file);
                    FlushLoaded(request->dest, request->size);
                    state = 8;
                }
            }
            FS_WaitAsync(reader->file);
            OS_RescheduleThread();
            break;
        case 4:
            FSi_WaitForCardThread();
            reader->blockLen[0] = FS_ReadFile(reader->file, request->dest + reader->blockLen[1], 0x200);
            if (reader->blockLen[0] == -1) {
                OS_Terminate();
            } else {
                reader->blockLen[1] += reader->blockLen[0];
                if (reader->blockLen[1] >= (int)request->size) {
                    FS_CloseFile(reader->file);
                    state = 8;
                }
            }
            OS_RescheduleThread();
            break;
        case 5:
            FSi_WaitForCardThread();
            NNS_SndArcLoadSeq(request->u.snd.dataId, request->u.snd.heap);
            *request->u.snd.statusOut = 2;
            state = 8;
            OS_RescheduleThread();
            break;
        case 6:
            FSi_WaitForCardThread();
            if (NNS_SndArcLoadSeqArc(request->u.snd.dataId, request->u.snd.heap) != 0) {
                FSi_WaitForCardThread();
                *request->u.snd.statusOut = NNS_SndArcLoadBank(request->u.snd.waveId, request->u.snd.heap) ? 2 : 3;
            } else {
                *request->u.snd.statusOut = 3;
            }
            state = 8;
            OS_RescheduleThread();
            break;
        case 7:
            FSi_WaitForCardThread();
            if (NNS_SndArcStrmPrepare(GetSoundStreamHandle(request->u.snd.dataId), request->u.snd.waveId, 0) != 0) {
                *request->u.snd.statusOut = 2;
            } else {
                *request->u.snd.statusOut = 3;
            }
            state = 8;
            OS_RescheduleThread();
            break;
        case 8:
            func_0202b880(request);
            state = 0;
            break;
        }
    }
}
