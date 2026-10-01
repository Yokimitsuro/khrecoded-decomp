typedef int BOOL;
typedef unsigned short u16;

#define REG_OS_IME (*(volatile u16 *)0x04000208)

extern BOOL OS_IsResetOccurred(void);
extern void OSi_ReloadRomData(BOOL isTwl);
extern void OSi_DoBoot(void);

void OSi_DoResetSystem(void)
{
    while (!OS_IsResetOccurred()) {
    }

    REG_OS_IME = 0;
    OSi_ReloadRomData(0);
    OSi_DoBoot();
}