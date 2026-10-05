#include "nitro/types.h"

typedef struct {
    s16 kind;
    s16 number;
} SessionName;

typedef struct {
    u8 pad[0x208];
    SessionName name;
} Session;

extern Session *data_ov001_020a0480;
extern const char data_ov001_0209e710[];
extern const char data_ov001_0209e714[];
extern void *OS_SPrintf(char *dst, const char *fmt, ...);

void FormatSessionNumber(int number, char *buffer) {
    SessionName *name = &data_ov001_020a0480->name;
    if (number != 0) {
        OS_SPrintf(buffer, data_ov001_0209e710, number, name);
        return;
    }
    OS_SPrintf(buffer, data_ov001_0209e714, name->number, name);
}
