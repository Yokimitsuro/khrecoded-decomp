#ifndef NITRO_SPI_PM_CALLBACK_INTERNAL_H
#define NITRO_SPI_PM_CALLBACK_INTERNAL_H

typedef unsigned int OSIntrMode;

typedef struct PMGenCallbackInfo {
    void (*callback)(void *argument);
    void *argument;
    int priority;
    struct PMGenCallbackInfo *next;
} PMGenCallbackInfo;

enum PMiCallbackCompareMethod {
    PMi_COMPARE_GT = 0,
    PMi_COMPARE_GE = 1
};

#define PM_CALLBACK_PRIORITY_MIN (-255)
#define PM_CALLBACK_PRIORITY_MAX 255

extern PMGenCallbackInfo *PMi_PreSleepCallbackList;
extern PMGenCallbackInfo *PMi_PostSleepCallbackList;

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode mode);

void PMi_InsertList(
    PMGenCallbackInfo **list,
    PMGenCallbackInfo *info,
    int priority,
    int method);
void PMi_DeleteList(PMGenCallbackInfo **list, PMGenCallbackInfo *info);
void PMi_ExecuteList(PMGenCallbackInfo *list);

#endif
