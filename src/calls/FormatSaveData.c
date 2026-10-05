#include "nitro/types.h"

typedef struct {
    u8 pad_00[2];
    u16 resourceId;
} CardThreadState;

extern CardThreadState data_0205fe00;
extern void *CARD_LockBackup(int id);
extern void CARD_UnlockBackup(int id);
extern int ReadCardBackupSync(u32 src, void *dst, u32 length);
extern BOOL FormatCardBackup(void);
extern void func_02026ef4(u32 mode);

BOOL FormatSaveData(void)
{
    u32 probe;
    BOOL success;

    CARD_LockBackup(data_0205fe00.resourceId);
    success = TRUE;
    if (ReadCardBackupSync(0, &probe, 1) != 0 || FormatCardBackup() == 0) {
        success = FALSE;
    }
    CARD_UnlockBackup(data_0205fe00.resourceId);
    func_02026ef4(1);
    return success;
}
