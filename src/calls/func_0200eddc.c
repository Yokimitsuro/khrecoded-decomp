typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *data_02057c38(void);
extern void OS_LockMutex(OverlayObjectFactory factory);
void func_0200eddc(void)
{
    OS_LockMutex(data_02057c38);
}
