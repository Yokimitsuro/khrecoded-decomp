#define NULL ((void *)0)
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef struct SNDBinaryFileHeader {
    char signature[4];
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
} SNDBinaryFileHeader;
typedef struct SNDBinaryBlockHeader { u32 kind; u32 size; } SNDBinaryBlockHeader;
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
    u32 instCount;
    u32 instOffset[0];
} SNDBankData;
extern void func_0200eddc(void);
extern void SNDi_UnlockMutex(void);
extern void DC_StoreRange(void *addr, u32 size);

void SND_AssignWaveArc(SNDBankData *bank, int index, SNDWaveArc *waveArc)
{
    SNDWaveArcLink *next;
    SNDWaveArcLink *prev;

    func_0200eddc();

    if (bank->waveArcLink[index].waveArc != NULL) {
        if (waveArc == bank->waveArcLink[index].waveArc) {
            SNDi_UnlockMutex();
            return;
        }

        if (&bank->waveArcLink[index] == bank->waveArcLink[index].waveArc->topLink) {
            bank->waveArcLink[index].waveArc->topLink = bank->waveArcLink[index].next;
            DC_StoreRange(bank->waveArcLink[index].waveArc, sizeof(SNDWaveArc));
        } else {
            prev = bank->waveArcLink[index].waveArc->topLink;
            while (prev != NULL) {
                if (&bank->waveArcLink[index] == prev->next)
                    break;
                prev = prev->next;
            }
            prev->next = bank->waveArcLink[index].next;
            DC_StoreRange(prev, sizeof(SNDWaveArcLink));
        }
    }

    next = waveArc->topLink;
    waveArc->topLink = &bank->waveArcLink[index];
    bank->waveArcLink[index].next = next;
    bank->waveArcLink[index].waveArc = waveArc;

    SNDi_UnlockMutex();
    DC_StoreRange(bank, sizeof(SNDBankData));
    DC_StoreRange(waveArc, sizeof(SNDWaveArc));
}