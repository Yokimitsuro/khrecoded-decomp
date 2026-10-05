#ifndef NNS_SNDARC_LOADER_INTERNAL_H
#define NNS_SNDARC_LOADER_INTERNAL_H

#include "libs/nns/snd/sndarc_internal.h"

typedef int NNSSndArcLoadResult;
typedef struct NNSSndSeqData {
    SNDBinaryFileHeader fileHeader;
    SNDBinaryBlockHeader blockHeader;
    u32 baseOffset;
    u32 data[1];
} NNSSndSeqData;

typedef struct NNSSndArcSeqInfo {
    u32 fileId;
    NNSSndSeqParam param;
} NNSSndArcSeqInfo;
typedef struct SNDWaveArcLink {
    struct SNDWaveArc *waveArc;
    struct SNDWaveArcLink *next;
} SNDWaveArcLink;

typedef struct SNDWaveArc {
    SNDBinaryFileHeader fileHeader;
    SNDBinaryBlockHeader blockHeader;
    SNDWaveArcLink *topLink;
    u32 reserved[7];
    u32 waveCount;
    u32 waveOffset[0];
} SNDWaveArc;

typedef struct SNDBankData {
    SNDBinaryFileHeader fileHeader;
    SNDBinaryBlockHeader blockHeader;
    SNDWaveArcLink waveArcLink[4];
    u32 instrumentCount;
    u32 instrumentOffset[0];
} SNDBankData;

typedef struct NNSSndArcBankInfo {
    u32 fileId;
    u16 waveArcNo[4];
} NNSSndArcBankInfo;

typedef struct NNSSndArcWaveArcInfo {
    u32 fileId : 24;
    u32 flags : 8;
} NNSSndArcWaveArcInfo;

typedef struct SNDInstParam {
    u16 wave[2];
    u8 originalKey;
    u8 attack;
    u8 decay;
    u8 sustain;
    u8 release;
    u8 pan;
} SNDInstParam;

typedef struct SNDInstData {
    u8 type;
    u8 padding;
    SNDInstParam parameter;
} SNDInstData;

typedef struct SNDInstPos {
    u32 programNo;
    u32 index;
} SNDInstPos;

typedef struct SNDWaveData SNDWaveData;

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
    NNS_SND_ARC_LOAD_BANK = 1 << 1,
    NNS_SND_ARC_LOAD_WAVE = 1 << 2,
    NNS_SND_ARC_LOAD_SEQARC = 1 << 3,
    NNS_SND_ARC_LOAD_ALL = 0xff,
    NNS_SND_ARC_INVALID_WAVEARC_NO = 0xffff,
    NNS_SND_ARC_BANK_TO_WAVEARC_COUNT = 4,
    NNS_SND_ARC_WAVEARC_SINGLE_LOAD = 1 << 0,
    SND_INST_PCM = 1
};

extern SNDWaveArc sWaveArcHeader;
extern u8 sWaveArcHeaderBuffer[0x3c];

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
extern NNSSndArcLoadResult NNSi_SndArcLoadWaveArc(
    int waveArcNo,
    u32 loadFlag,
    NNSSndHeapHandle heap,
    BOOL setAddress,
    SNDWaveArc **data);
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
extern SNDWaveArc *NNS_SndArcLoadWaveArcTable(
    u32 fileId,
    NNSSndHeapHandle heap,
    BOOL setAddress);
extern BOOL LoadSingleWaves(
    SNDWaveArc *waveArc,
    const SNDBankData *bank,
    int waveArcNo,
    u32 fileId,
    NNSSndHeapHandle heap);
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
extern const NNSSndArcBankInfo *NNS_SndArcGetBankInfo(int bankNo);
extern const NNSSndArcWaveArcInfo *NNS_SndArcGetWaveArcInfo(int waveArcNo);
extern void SND_AssignWaveArc(
    SNDBankData *bank,
    int index,
    SNDWaveArc *waveArc);
extern const SNDWaveData *SND_GetWaveDataAddress(
    const SNDWaveArc *waveArc,
    int waveNo);
extern u32 SND_GetWaveDataCount(const SNDWaveArc *waveArc);
extern void SND_SetWaveDataAddress(
    SNDWaveArc *waveArc,
    int waveNo,
    const SNDWaveData *address);
extern SNDInstPos SND_GetFirstInstDataPos(const SNDBankData *bank);
extern BOOL SND_GetNextInstData(
    const SNDBankData *bank,
    SNDInstData *instrument,
    SNDInstPos *position);
extern BOOL SndLoadWaveData(
    SNDWaveArc *waveArc,
    int waveNo,
    u32 fileId,
    NNSSndHeapHandle heap);
extern void MI_CpuCopy8(const void *source, void *destination, u32 size);
extern void MI_CpuFill8(void *destination, u8 value, u32 size);
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
extern void WaveArcTableDisposeCallback(
    void *memory,
    u32 size,
    u32 data1,
    u32 data2);
extern NNSSndArc *SND_SetActiveSlotSwap(NNSSndArc *arc);

#endif
