typedef unsigned int u32;
typedef struct SNDInstPos { u32 prgNo; u32 index; } SNDInstPos;
typedef struct SNDBankData SNDBankData;
SNDInstPos SND_GetFirstInstDataPos(const SNDBankData *bank)
{
    SNDInstPos pos;
    (void)bank;
    pos.prgNo = 0;
    pos.index = 0;
    return pos;
}