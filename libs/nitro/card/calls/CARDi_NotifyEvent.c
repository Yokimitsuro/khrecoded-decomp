typedef unsigned long u32;
typedef u32 CARDEvent;
typedef unsigned long OSIntrMode;

typedef void (*CARDHookFunction)(void *userData, CARDEvent event,
                                 void *argument);

typedef struct CARDHookContext {
    struct CARDHookContext *next;
    void *userData;
    CARDHookFunction callback;
} CARDHookContext;

static CARDHookContext *CARDiHookChain;
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode mode);

void CARDi_NotifyEvent(CARDEvent event, void *argument)
{
    OSIntrMode previousMode = OS_DisableInterrupts();
    CARDHookContext **link = &CARDiHookChain;

    while (*link) {
        CARDHookContext *hook = *link;

        if (hook->callback) {
            (*hook->callback)(hook->userData, event, argument);
        }
        if (*link == hook) {
            link = &(*link)->next;
        }
    }

    (void)OS_RestoreInterrupts(previousMode);
}