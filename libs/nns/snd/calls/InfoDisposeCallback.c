typedef unsigned int u32;
typedef unsigned char u8;

typedef struct NNSSndArc {
    u8 reserved[0x90];
    void *fat;
    void *symbol;
    void *info;
} NNSSndArc;

void InfoDisposeCallback(void *mem, u32 size, u32 data1, u32 data2)
{
    NNSSndArc *arc = (NNSSndArc *)data1;

    arc->info = 0;
}