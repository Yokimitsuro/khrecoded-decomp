typedef int BOOL;
typedef struct CARDiCommon CARDiCommon;

extern CARDiCommon cardi_common;
extern BOOL CARDi_WaitForTask(CARDiCommon *common, BOOL asynchronous,
                              void (*callback)(void *), void *argument);

BOOL CARDi_WaitAsync(void)
{
    return CARDi_WaitForTask(&cardi_common, 0, 0, 0);
}