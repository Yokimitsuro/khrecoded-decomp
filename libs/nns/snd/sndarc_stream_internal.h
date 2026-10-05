#ifndef NNS_SNDARC_STREAM_INTERNAL_H
#define NNS_SNDARC_STREAM_INTERNAL_H

#include "libs/nns/snd/sndarc_loader_internal.h"

enum {
    NNS_SND_STRM_PLAYER_NUM = 4,
    NNS_SND_STRM_COMMAND_NUM = 8,
    NNS_SND_STRM_BLOCK_SIZE = 512,
    NNS_SND_STRM_BLOCK_NUM = 4,
    NNS_SND_STRM_PLAYER_ACTIVE = 1 << 0,
    NNS_SND_STRM_PLAYER_STARTING = 1 << 2
};

typedef struct NNSFndList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef struct NNSSndStrmCommand {
    void *previous;
    void *next;
    u32 parameter[10];
} NNSSndStrmCommand;

typedef struct NNSSndArcStreamState {
    BOOL initialized;
    void *prepareThread;
    u8 *decodeBuffer;
} NNSSndArcStreamState;

typedef struct NNSSndStrmPlayer {
    u8 streamStorage[0x64];
    u8 fileStorage[0xb4];
    u32 flags;
    u8 reserved11c[0x0c];
    int allocChannelCount;
    u8 numChannels;
    u8 padding12d;
    u8 channelNumbers[6];
    void *buffer;
    u32 bufferSize;
    u8 reserved13c[0x14];
    int playerNo;
    u8 reserved154[0x28];
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

typedef void (*NNSSndStrmCallback)(void);
typedef void (*NNSSndArcStrmCallback)(void);

typedef struct NNSSndStrmThread {
    u8 storage[0x18c];
} NNSSndStrmThread;

extern NNSSndArcStreamState sSoundArcStreamState;
extern NNSFndList sFreeStreamCommandList;
extern u8 sStreamCommandMutex[0x18];
extern NNSSndStrmCommand sStreamCommands[NNS_SND_STRM_COMMAND_NUM];
extern u8 sDecodeBufferArea[0x200];
extern NNSSndStrmPlayer sStrmPlayers[NNS_SND_STRM_PLAYER_NUM];
extern NNSSndStrmThread sPrepareStreamThread;

extern void NNS_FndInitList(NNSFndList *list, u16 offset);
extern void NNS_FndAppendListObject(NNSFndList *list, void *object);
extern void OS_InitMutex(void *mutex);
extern void FS_InitFile(FSFile *file);
extern void NNS_SndStrmInit(void *stream);
extern void CreateThread(NNSSndStrmThread *thread, u32 threadPriority);
extern const NNSSndArcStrmPlayerInfo *NNS_SndArcGetStrmPlayerInfo(
    int playerNo);
extern const NNSSndArcStrmInfo *NNS_SndArcGetStrmInfo(int streamNo);
extern void ForceStopStrm_2(NNSSndStrmPlayer *player);
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
