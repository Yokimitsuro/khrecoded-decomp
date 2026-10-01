typedef unsigned char u8;
typedef unsigned int u32;

typedef struct NNSSndArcOffsetTable {
    u32 count;
    u32 offsets[1];
} NNSSndArcOffsetTable;

typedef struct NNSSndArcInfo {
    u8 header[8];
    u32 seqOffset;
    u32 seqArcOffset;
    u32 bankOffset;
    u32 waveArcOffset;
    u32 playerInfoOffset;
    u32 groupOffset;
    u32 strmPlayerInfoOffset;
    u32 strmOffset;
} NNSSndArcInfo;

typedef struct NNSSndArc {
    u8 reserved[0x98];
    NNSSndArcInfo *info;
} NNSSndArc;

extern NNSSndArc *sCurrentSoundArchive;

static inline const void *GetPtrConst(const void *base, u32 offset)
{
    if (offset == 0) return 0;
    return (const u8 *)base + offset;
}

static inline const NNSSndArcOffsetTable *GetOffsetTable(const NNSSndArcInfo *info, u32 offset)
{
    return (const NNSSndArcOffsetTable *)GetPtrConst(info, offset);
}

const void *NNS_SndArcGetWaveArcInfo(int index)
{
    NNSSndArc *arc = sCurrentSoundArchive;
    const NNSSndArcOffsetTable *table;

    table = GetOffsetTable(arc->info, arc->info->waveArcOffset);
    if (table == 0) return 0;
    if (index < 0) return 0;
    if (index >= table->count) return 0;
    return GetPtrConst(arc->info, table->offsets[index]);
}