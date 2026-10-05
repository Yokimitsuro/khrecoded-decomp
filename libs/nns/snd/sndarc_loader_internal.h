#ifndef NNS_SNDARC_LOADER_INTERNAL_H
#define NNS_SNDARC_LOADER_INTERNAL_H

#include "libs/nns/snd/sndarc_internal.h"

typedef int NNSSndArcLoadResult;
typedef struct NNSSndSeqParam {
    u16 bankNo;
    u8 volume;
    u8 channelPriority;
    u8 playerPriority;
    u8 playerNo;
    u16 reserved;
} NNSSndSeqParam;

typedef struct NNSSndSeqData {
    SNDBinaryFileHeader fileHeader;
    SNDBinaryBlockHeader blockHeader;
    u32 baseOffset;
    u32 data[1];
} NNSSndSeqData;

typedef struct NNSSndArcSeqInfo {
    u32 fileId;
    NNSSndSeqParam parameter;
} NNSSndArcSeqInfo;
typedef struct SNDBankData SNDBankData;
typedef struct SNDWaveArc SNDWaveArc;

enum {
    NNS_SND_ARC_LOAD_SUCCESS = 0,
    NNS_SND_ARC_LOAD_ERROR_INVALID_GROUP_NO,
    NNS_SND_ARC_LOAD_ERROR_INVALID_SEQ_NO,
    NNS_SND_ARC_LOAD_ERROR_INVALID_SEQARC_NO,
    NNS_SND_ARC_LOAD_ERROR_INVALID_BANK_NO,
    NNS_SND_ARC_LOAD_ERROR_INVALID_WAVEARC_NO,
    NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_SEQ,
    NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_SEQARC,
    NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_BANK,
    NNS_SND_ARC_LOAD_ERROR_FAILED_LOAD_WAVE,
    NNS_SND_ARC_LOAD_SEQ = 1 << 0,
    NNS_SND_ARC_LOAD_SEQARC = 1 << 3,
    NNS_SND_ARC_LOAD_ALL = 0xff
};

extern NNSSndArcLoadResult NNSi_SndArcLoadSeq(
    int seqNo,
    u32 loadFlag,
    NNSSndHeapHandle heap,
    BOOL setAddress,
    NNSSndSeqData **data);
extern NNSSndArcLoadResult NNSi_SndArcLoadSeqArc(
    int seqArcNo,
    u32 loadFlag,
    NNSSndHeapHandle heap,
    BOOL setAddress,
    NNSSndSeqArc **data);
extern NNSSndArcLoadResult NNSi_SndArcLoadBank(
    int bankNo,
    u32 loadFlag,
    NNSSndHeapHandle heap,
    BOOL setAddress,
    SNDBankData **data);
extern const NNSSndArcSeqInfo *NNS_SndArcGetSeqInfo(int seqNo);
extern NNSSndSeqData *LoadSeq(
    u32 fileId,
    NNSSndHeapHandle heap,
    BOOL setAddress);
extern NNSSndSeqArc *LoadSeqArc(
    u32 fileId,
    NNSSndHeapHandle heap,
    BOOL setAddress);
extern SNDBankData *LoadBank(
    u32 fileId,
    NNSSndHeapHandle heap,
    BOOL setAddress);
extern SNDWaveArc *LoadWaveArc(
    u32 fileId,
    NNSSndHeapHandle heap,
    BOOL setAddress);
extern NNSSndArc *NNS_SndArcGetCurrent(void);
extern void NNS_SndArcSetFileAddress(u32 fileId, void *address);
extern void *NNSi_SndArcLoadFile(
    u32 fileId,
    NNSSndHeapDisposeCallback callback,
    u32 data1,
    u32 data2,
    NNSSndHeapHandle heap);
extern void SeqDisposeCallback(
    void *memory,
    u32 size,
    u32 data1,
    u32 data2);
extern u32 NNS_SndArcGetFileSize(u32 fileId);
extern int NNS_SndArcReadFile(
    u32 fileId,
    void *buffer,
    int size,
    int offset);
extern void DC_StoreRange(const void *startAddress, u32 size);
extern void DisposeCallback(
    void *memory,
    NNSSndArc *arc,
    u32 fileId);
extern void SND_InvalidateSeqData(const void *start, const void *end);
extern void SND_InvalidateBankData(const void *start, const void *end);
extern void SND_InvalidateWaveData(const void *start, const void *end);
extern void SND_DestroyBank(SNDBankData *bank);
extern void SND_DestroyWaveArc(SNDWaveArc *waveArc);
extern void BankDisposeCallback(
    void *memory,
    u32 size,
    u32 data1,
    u32 data2);
extern void WaveArcDisposeCallback(
    void *memory,
    u32 size,
    u32 data1,
    u32 data2);
extern NNSSndArc *SND_SetActiveSlotSwap(NNSSndArc *arc);

#endif
