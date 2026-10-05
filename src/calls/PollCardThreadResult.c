#include "nitro/types.h"

typedef struct SignedBlob {
    s32 magic;
    u8 hash[0x14];
    u8 data[0x3760];
} SignedBlob;

typedef struct {
    u8 blockCounter;
    u8 slot;
    u8 pad_02[6];
    SignedBlob *buffer;
    void *payload;
} CardThreadState;

extern CardThreadState data_0205fe00;
extern int PollCardTransferThread(void);
extern BOOL VerifySha1Signature(SignedBlob *blob);
extern void StartCardTransferThread(void *src, void *dst, u32 length);
extern void DecrementBusyCounterIfPositive(void);

int PollCardThreadResult(void)
{
    int status;
    int *word;
    u32 i;
    int result;

    status = PollCardTransferThread();
    if (status < 0) {
        goto busy;
    }
    if (status != 0) {
        result = 3;
    } else {
        word = (int *)data_0205fe00.buffer;
        for (i = 0; i < 8; i++) {
            if (*word++ != 0) {
                break;
            }
        }
        if (i == 8) {
            result = 2;
        } else if (VerifySha1Signature(data_0205fe00.buffer) != 0) {
            result = 0;
            data_0205fe00.payload = (u8 *)data_0205fe00.buffer + 0x18;
        } else {
            data_0205fe00.blockCounter = data_0205fe00.blockCounter + 1;
            if (data_0205fe00.blockCounter >= 2) {
                result = 4;
            } else {
                StartCardTransferThread(
                    (void *)((data_0205fe00.blockCounter + data_0205fe00.slot * 2) * 0x3c18 + 0x20),
                    data_0205fe00.buffer, 0x3c18);
                return 1;
            }
        }
    }
    goto tail;
busy:
    return 1;
tail:
    DecrementBusyCounterIfPositive();
    return result;
}
