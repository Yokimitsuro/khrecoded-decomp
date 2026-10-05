extern unsigned long long OS_GetTick(void);

typedef struct {
    unsigned short wStart;
    unsigned short wCurrent;
    unsigned short wKind;
    unsigned short wPriority;
    char pad0008[8];
    unsigned long long qwStartedAt;
    int bRunning;
} Ov002Countdown;

void ArmCountdown(Ov002Countdown *self, unsigned short value,
                         unsigned short kind) {
    self->wKind = kind;
    self->wPriority = 7;

    if (self->bRunning != 0) {
        return;
    }

    self->wStart = value;
    self->wCurrent = value;
    self->qwStartedAt = OS_GetTick();
    self->bRunning = 1;
}
