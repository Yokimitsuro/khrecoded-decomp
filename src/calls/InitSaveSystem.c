#include "nitro/types.h"

typedef void (*CardDoneSetter)(void);
typedef u32 (*CallbackInvoker)(CardDoneSetter setter);

typedef struct {
    u8 pad_00[2];
    u16 resourceId;
    u8 pad_04[4];
    void *buffer;
} CardThreadState;

extern CardThreadState data_0205fe00;
extern void **data_02060394;
extern u8 gSaveCheckOverlayId[];
extern void func_02029f8c(int processor, int overlayId);
extern void func_02029fac(int processor, int overlayId);
extern void __DSProt_DetectEmulator(CallbackInvoker invoker, CardDoneSetter setter, int flags);
extern u32 __DSProt_DetectNotFlashcart(CallbackInvoker invoker, CardDoneSetter setter, int flags);
extern u32 __DSProt_DetectNotDummy(CallbackInvoker invoker, CardDoneSetter setter, int flags);
extern u32 InvokeOptionalCallback(CardDoneSetter callback);
extern void SetCardThreadDoneCallback(void);
extern void SetCardThreadDoneCallback_02026b04(void);
extern s32 OS_GetLockID(void);
extern void OS_Terminate(void);
extern void *AllocFromHeapOrDefaultEx(u32 size, int align, void **heap);
extern void *CARD_LockBackup(int id);
extern void CARD_UnlockBackup(int id);
extern BOOL CARD_IdentifyBackup(int backupType);
extern int VerifyCardIdMatchesReference(void);
extern void func_02026ef4(u32 mode);

int InitSaveSystem(void)
{
    int result = 0;
    BOOL verified;
    CardDoneSetter setter;

    if (data_0205fe00.buffer != NULL) {
        return result;
    }
    func_02029f8c(0, (int)gSaveCheckOverlayId);
    __DSProt_DetectEmulator(InvokeOptionalCallback, SetCardThreadDoneCallback_02026b04, 0);
    verified = __DSProt_DetectNotFlashcart(InvokeOptionalCallback, SetCardThreadDoneCallback, 0) ==
               ~(u32)SetCardThreadDoneCallback;
    if (!verified) {
        setter = NULL;
        verified = __DSProt_DetectNotDummy(InvokeOptionalCallback, setter, 0) == ~(u32)setter;
        if (verified) {
            result = 0;
        }
        SetCardThreadDoneCallback_02026b04();
    }
    func_02029fac(0, (int)gSaveCheckOverlayId);
    data_0205fe00.resourceId = OS_GetLockID();
    if (data_0205fe00.resourceId == -3) {
        OS_Terminate();
    }
    data_0205fe00.buffer = AllocFromHeapOrDefaultEx(0x3c18, 0x20, data_02060394);
    CARD_LockBackup(data_0205fe00.resourceId);
    if (CARD_IdentifyBackup(0x1001) == 0) {
        result = 3;
    } else if (VerifyCardIdMatchesReference() == 0) {
        result = 5;
    }
    CARD_UnlockBackup(data_0205fe00.resourceId);
    func_02026ef4(1);
    return result;
}
