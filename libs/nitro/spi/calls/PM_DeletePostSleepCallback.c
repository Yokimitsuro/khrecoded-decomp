extern void PMi_DeleteList(void *list, void *info);
extern int PMi_PostSleepCallbackList;

void PM_DeletePostSleepCallback(void *info)
{
    PMi_DeleteList(&PMi_PostSleepCallbackList, info);
}
