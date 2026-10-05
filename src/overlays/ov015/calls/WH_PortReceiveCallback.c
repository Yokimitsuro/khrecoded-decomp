#include "nitro/types.h"

typedef void (*WhReceiverFunc)(u16 aid, u16 *data, u16 size);

typedef struct WMPortRecvCallback {
    u16 apiid;
    u16 errcode;
    u16 state;
    u16 port;
    u16 restSize;
    u16 reserved;
    u16 *data;
    u16 length;
    u16 aid;
} WMPortRecvCallback;

typedef struct WirelessHelper {
    u8 pad_00[0x44];
    WhReceiverFunc receiver;
} WirelessHelper;

extern WirelessHelper data_ov015_0207e980;
extern void WH_SetError(int code);

void WH_PortReceiveCallback(void *arg)
{
    WMPortRecvCallback *cb = (WMPortRecvCallback *)arg;

    if (cb->errcode != 0) {
        WH_SetError(cb->errcode);
    } else if (data_ov015_0207e980.receiver != NULL) {
        if (cb->state == 21) {
            data_ov015_0207e980.receiver(cb->aid, cb->data, cb->length);
        } else if (cb->state == 9) {
            data_ov015_0207e980.receiver(cb->aid, NULL, 0);
        }
    }
}
