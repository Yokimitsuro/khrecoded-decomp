#ifndef RECODED_OV039_RUNTIME_STATE_H
#define RECODED_OV039_RUNTIME_STATE_H

typedef struct RuntimeStateTail {
    unsigned char padding_0000[0x9c4];
    int mode;
    unsigned char padding_09c8[0x4c];
    int condition;
    unsigned char padding_0a18[0x68];
    int flags;
    unsigned char padding_0a84[0x64];
    int objectId;
} RuntimeStateTail;

extern void *data_ov039_020bea20;

#define RUNTIME_STATE_TAIL \
    ((RuntimeStateTail *)((unsigned char *)data_ov039_020bea20 + 0xc000))

#endif
