typedef struct NNSSndStrm {
    unsigned char padding00[0x2c];
    unsigned int active : 1;
    unsigned int start : 1;
    unsigned char padding30[0x18];
    int alarmNumber;
} NNSSndStrm;

extern unsigned char data_0205e17c;
extern void SND_ClearChannelBit(int alarmNumber);
extern void NNS_FndRemoveListObject(void *list, void *object);

void ShutdownStrm(NNSSndStrm *stream)
{
    SND_ClearChannelBit(stream->alarmNumber);
    NNS_FndRemoveListObject(&data_0205e17c, stream);
    stream->active = 0;
}
