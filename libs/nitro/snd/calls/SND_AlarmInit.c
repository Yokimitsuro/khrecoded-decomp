typedef struct SNDAlarm {
    void *handler;
    void *argument;
    unsigned char id;
    unsigned char padding[3];
} SNDAlarm;

extern SNDAlarm data_02059720[8];

void SND_AlarmInit(void)
{
    int i;

    for (i = 0; i < 8; i++) {
        data_02059720[i].handler = 0;
        data_02059720[i].argument = 0;
        data_02059720[i].id = 0;
    }
}