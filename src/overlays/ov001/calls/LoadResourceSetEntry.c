#include "nitro/types.h"

typedef struct {
    u32 words[17];
} SetHeader;

typedef struct {
    u32 words[8];
} SetEntry;

typedef struct {
    u8 pad_00[0xc];
    SetHeader *headers;
    u8 pad_10[0xc];
    SetEntry (*entries)[8];
} SetTableData;

typedef struct {
    u8 pad_00[8];
    SetTableData *data;
} SetTableFile;

extern char sOv001_EnPaEPBin_020a045c[];
extern SetTableFile *Archive_LoadFile(const char *path, u32 flags);
extern void RelocateResourceTable(SetTableFile *table);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

BOOL LoadResourceSetEntry(int setIndex, SetHeader *header, SetEntry *entries)
{
    SetTableFile *file = Archive_LoadFile(sOv001_EnPaEPBin_020a045c, 11);
    u16 i;

    if (file != NULL) {
        SetEntry (*table)[8];
        RelocateResourceTable(file);
        table = file->data->entries;
        *header = file->data->headers[setIndex];
        for (i = 0; i < 8; i++) {
            entries[i] = table[setIndex][i];
        }
        NNSi_FndFreeFromDefaultHeap(file);
    }
    return TRUE;
}
