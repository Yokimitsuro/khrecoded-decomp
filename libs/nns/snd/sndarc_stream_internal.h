#ifndef NNS_SNDARC_STREAM_INTERNAL_H
#define NNS_SNDARC_STREAM_INTERNAL_H

#include "libs/nns/snd/sndarc_loader_internal.h"

enum {
    NNS_SND_STRM_PLAYER_NUM = 4,
    NNS_SND_STRM_COMMAND_NUM = 8,
    NNS_SND_STRM_BLOCK_SIZE = 512,
    NNS_SND_STRM_BLOCK_NUM = 4,
    NNS_SND_STRM_PLAYER_ACTIVE = 1 << 0,
    NNS_SND_STRM_PLAYER_STARTING = 1 << 2,
    NNS_SND_ARC_STRM_FORCE_STEREO = 1 << 0
};

enum {
    NNS_SND_ADPCM_INDEX_COUNT = 89
};

typedef struct NNSFndList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

struct NNSSndStrmPlayer;
typedef struct NNSSndStrmThread NNSSndStrmThread;

typedef struct NNSSndStrmCommand {
    void *previous;
    void *next;
    struct NNSSndStrmPlayer *player;
    int status;
    int numChannels;
    void *buffers[6];
    u32 bufferLength;
} NNSSndStrmCommand;

typedef struct NNSSndArcStreamState {
    BOOL initialized;
    NNSSndStrmThread *prepareThread;
    u8 *decodeBuffer;
} NNSSndArcStreamState;

typedef enum NNSSndStrmFormat {
    NNS_SND_STRM_FORMAT_PCM8,
    NNS_SND_STRM_FORMAT_PCM16
} NNSSndStrmFormat;

typedef enum NNSSndStrmCallbackStatus {
    NNS_SND_STRM_CALLBACK_SETUP,
    NNS_SND_STRM_CALLBACK_INTERVAL
} NNSSndStrmCallbackStatus;

typedef enum NNSSndArcStrmCallbackStatus {
    NNS_SND_ARC_STRM_CALLBACK_DATA_END
} NNSSndArcStrmCallbackStatus;

typedef struct NNSSndArcStrmCallbackInfo {
    int playerNo;
    int streamNo;
} NNSSndArcStrmCallbackInfo;

typedef struct NNSSndArcStrmCallbackParam {
    int streamNo;
    u32 offset;
} NNSSndArcStrmCallbackParam;

typedef enum NNSSndStrmDataFormat {
    NNS_SND_STRM_DATA_FORMAT_PCM8,
    NNS_SND_STRM_DATA_FORMAT_PCM16,
    NNS_SND_STRM_DATA_FORMAT_ADPCM
} NNSSndStrmDataFormat;

typedef struct NNSSndStrm {
    u8 storage[0x5c];
} NNSSndStrm;

typedef struct NNSSndFader {
    int origin;
    int target;
    int counter;
    int frame;
} NNSSndFader;

typedef struct NNSSndStrmData {
    SNDBinaryFileHeader fileHeader;
    SNDBinaryBlockHeader blockHeader;
    u8 format;
    u8 loopFlag;
    u8 numChannels;
    u8 padding;
    u16 sampleRate;
    u16 timer;
    u32 loopStart;
    u32 loopEnd;
    u32 dataOffset;
    u32 numBlocks;
    u32 blockSize;
    u32 blockSamples;
    u32 lastBlockSize;
    u32 lastBlockSamples;
} NNSSndStrmData;

typedef struct NNSSndAdpcmState {
    short previousSample;
    u8 previousIndex;
    u8 padding;
} NNSSndAdpcmState;

typedef void (*NNSSndStrmCallback)(
    NNSSndStrmCallbackStatus status,
    int numChannels,
    void *buffers[],
    u32 length,
    NNSSndStrmFormat format,
    void *argument);
typedef BOOL (*NNSSndArcStrmCallback)(
    NNSSndArcStrmCallbackStatus status,
    const NNSSndArcStrmCallbackInfo *info,
    NNSSndArcStrmCallbackParam *parameter,
    void *argument);
typedef BOOL (*NNSSndOpenStreamFunction)(
    struct NNSSndStrmPlayer *player,
    u32 fileId);
typedef void (*NNSSndCloseStreamFunction)(
    struct NNSSndStrmPlayer *player);
typedef int (*NNSSndReadStreamFunction)(
    struct NNSSndStrmPlayer *player,
    void *destination,
    u32 size,
    u32 offset);
typedef void (*NNSSndCancelStreamFunction)(
    struct NNSSndStrmPlayer *player);

typedef struct NNSSndStrmPlayer {
    NNSSndStrm stream;
    u32 reservedAfterStream[2];
    u8 fileStorage[0x48];
    u32 fileOffset;
    NNSSndStrmData info;
    NNSSndFader fader;
    NNSSndAdpcmState adpcmState[6];
    BOOL activeFlag : 1;
    BOOL playFlag : 1;
    BOOL startFlag : 1;
    BOOL fadeOutFlag : 1;
    BOOL dirtyFlag : 1;
    BOOL finishFlag : 1;
    BOOL monoFlag : 1;
    BOOL reservedFlags : 25;
    volatile int finishCounter;
    volatile BOOL prepareFlag;
    volatile int commandCount;
    int allocChannelCount;
    u8 numChannels;
    u8 padding12d;
    u8 channelNumbers[6];
    void *buffer;
    u32 bufferSize;
    NNSSndStrmCallback streamCallback;
    void *streamCallbackArgument;
    NNSSndArcStrmCallback archiveCallback;
    void *archiveCallbackArgument;
    int streamNo;
    int playerNo;
    struct NNSSndStrmHandle *handle;
    int priority;
    int initialVolume;
    int externalVolume;
    int volume;
    u32 currentSample;
    NNSSndOpenStreamFunction openStream;
    NNSSndCloseStreamFunction closeStream;
    NNSSndReadStreamFunction readStream;
    NNSSndCancelStreamFunction cancelStream;
} NNSSndStrmPlayer;

typedef struct NNSSndStrmHandle {
    NNSSndStrmPlayer *player;
} NNSSndStrmHandle;

typedef struct NNSSndArcStrmPlayerInfo {
    u8 numChannels;
    u8 channelNumbers[2];
} NNSSndArcStrmPlayerInfo;

typedef struct NNSSndArcStrmInfo {
    u32 fileId;
    u8 volume;
    u8 playerPriority;
    u8 playerNo;
    u8 flags;
} NNSSndArcStrmInfo;

struct NNSSndStrmThread {
    u8 thread[0xc0];
    u8 stack[0x1000];
    OSThreadQueue threadQueue;
    u8 mutex[0x18];
    NNSFndList commandList;
};

extern NNSSndArcStreamState sSoundArcStreamState;
extern NNSFndList sFreeStreamCommandList;
extern u8 sDecodeBufferMutex[0x18];
extern NNSSndStrmCommand sStreamCommands[NNS_SND_STRM_COMMAND_NUM];
extern u8 sDecodeBufferArea[0x200];
extern NNSSndStrmPlayer sStrmPlayers[NNS_SND_STRM_PLAYER_NUM];
extern NNSSndStrmThread sPrepareStreamThread;
extern NNSFndList sStreamCommandList;
extern u8 sSoundArcStreamMutex[0x18];
extern const signed char cAdpcmIndexTable[16];
extern const short cAdpcmStepSizeTable[NNS_SND_ADPCM_INDEX_COUNT];

extern void NNS_FndInitList(NNSFndList *list, u16 offset);
extern void NNS_FndAppendListObject(NNSFndList *list, void *object);
extern void *NNS_FndGetNextListObject(NNSFndList *list, void *object);
extern void NNS_FndRemoveListObject(NNSFndList *list, void *object);
extern u32 OS_DisableInterrupts(void);
extern u32 OS_RestoreInterrupts(u32 state);
extern void OS_InitMutex(void *mutex);
extern void OS_LockMutex(void *mutex);
extern void OS_UnlockMutex(void *mutex);
extern void DC_FlushRange(const void *address, u32 size);
extern void OS_CreateThread(
    void *thread,
    void (*entry)(void *),
    void *argument,
    void *stackTop,
    u32 stackSize,
    u32 priority);
extern void OS_WakeupThreadDirect(void *thread);
extern void OS_WakeupThread(OSThreadQueue *queue);
extern void FS_InitFile(FSFile *file);
extern BOOL FS_CloseFile(FSFile *file);
extern void FS_CancelFile(FSFile *file);
extern BOOL FS_SetSeekCache(FSFile *file, void *buffer, u32 bufferSize);
extern void NNS_SndStrmInit(void *stream);
extern BOOL NNS_SndStrmSetup(
    NNSSndStrm *stream,
    NNSSndStrmFormat format,
    void *buffer,
    u32 bufferSize,
    int timer,
    int interval,
    NNSSndStrmCallback callback,
    void *argument);
extern void NNS_SndStrmSetChannelPan(
    NNSSndStrm *stream,
    int channelNo,
    int pan);
extern void NNS_SndStrmFreeChannel(NNSSndStrm *stream);
extern void CreateThread(NNSSndStrmThread *thread, u32 threadPriority);
extern void StrmThread(void *argument);
extern void OS_SleepThread(OSThreadQueue *queue);
extern const NNSSndArcStrmPlayerInfo *NNS_SndArcGetStrmPlayerInfo(
    int playerNo);
extern const NNSSndArcStrmInfo *NNS_SndArcGetStrmInfo(int streamNo);
extern u32 NNS_SndArcGetFileOffset(u32 fileId);
extern FSFileID NNS_SndArcGetFileID(void);
extern const char *NNSi_SndArcGetFilePath(void);
extern void *NNSi_SndArcGetSeekCacheBuffer(void);
extern u32 NNSi_SndArcGetSeekCacheSize(void);
extern void ForceStopStrm_2(NNSSndStrmPlayer *player);
extern void ShutdownStreamPlayer(NNSSndStrmPlayer *player);
extern NNSSndStrmPlayer *AllocPlayer(
    NNSSndStrmHandle *handle,
    int playerNo,
    int priority);
extern void FreePlayer(NNSSndStrmPlayer *player);
extern BOOL AllocChannel(
    NNSSndStrmPlayer *player,
    int numChannels,
    const u8 channelNumbers[]);
extern void FreeChannel(NNSSndStrmPlayer *player);
extern void StrmCallback_2(
    NNSSndStrmCallbackStatus status,
    int numChannels,
    void *buffers[],
    u32 length,
    NNSSndStrmFormat format,
    void *argument);
extern void SetupStreamFunction(NNSSndStrmPlayer *player, u32 fileId);
extern void RemoveCommandByPlayer(
    NNSFndList *commandList,
    const NNSSndStrmPlayer *player);
extern NNSSndStrmCommand *AllocCommandBuffer(void);
extern void FreeCommandBuffer(NNSSndStrmCommand *command);
extern NNSSndStrmCommand *ReadCommandBuffer(NNSFndList *commandList);
extern void OnDataEnd(NNSSndStrmPlayer *player);
extern void NNSi_SndArcStrm_MakeWaveData(NNSSndStrmCommand *command);
extern BOOL OpenFileStream(NNSSndStrmPlayer *player, u32 fileId);
extern void CloseFileStream(NNSSndStrmPlayer *player);
extern int ReadFileStream(
    NNSSndStrmPlayer *player,
    void *destination,
    u32 size,
    u32 offset);
extern void CancelFileStream(NNSSndStrmPlayer *player);
extern BOOL OpenMemoryStream(NNSSndStrmPlayer *player, u32 fileId);
extern void CloseMemoryStream(NNSSndStrmPlayer *player);
extern int ReadMemoryStream(
    NNSSndStrmPlayer *player,
    void *destination,
    u32 size,
    u32 offset);
extern void CancelMemoryStream(NNSSndStrmPlayer *player);
extern void NNSi_SndFaderInit(NNSSndFader *fader);
extern void NNSi_SndFaderSet(
    NNSSndFader *fader,
    int target,
    int frameCount);
extern void DisposeCallback_2(
    void *memory,
    u32 size,
    u32 data1,
    u32 data2);
extern BOOL PrepareStrm(
    NNSSndStrmHandle *handle,
    const NNSSndArcStrmInfo *streamInfo,
    int playerNo,
    int playerPriority,
    int streamNo,
    u32 offset,
    NNSSndStrmCallback streamCallback,
    void *streamCallbackArgument,
    NNSSndArcStrmCallback archiveCallback,
    void *archiveCallbackArgument);
extern void SNDi_FreeVoiceChannel(
    NNSSndStrmPlayer *player,
    int fadeFrames);
extern BOOL NNS_SndArcStrmSetupPlayer(NNSSndHeapHandle heap);
extern BOOL NNS_SndArcStrmPrepare(
    NNSSndStrmHandle *handle,
    int streamNo,
    u32 offset);
extern void NNS_SndArcStrmStartPrepared(NNSSndStrmHandle *handle);

#endif
