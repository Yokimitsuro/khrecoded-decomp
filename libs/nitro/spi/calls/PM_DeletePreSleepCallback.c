extern void PMi_DeleteList(void *list, void *info);
extern int PMi_PreSleepCallbackList;

void PM_DeletePreSleepCallback(void *info)
{
    PMi_DeleteList(&PMi_PreSleepCallbackList, info);
}
