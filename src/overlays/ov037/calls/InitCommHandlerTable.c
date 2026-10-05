#include "nitro/types.h"

typedef struct CommHandlerTable {
    void *open;
    void *start;
    void *poll;
    void *reserved0;
    void *isActive;
    void *release;
    void *apply;
    void *reserved1;
    void *update;
    void *close;
} CommHandlerTable;

extern void func_ov037_020bab98(void);
extern void func_ov037_020babbc(void);
extern void func_ov037_020babe8(void);
extern void IsPxiChannelActive(void);
extern void ReleasePxiChannel(void);
extern void func_ov037_020bac50(void);
extern void func_ov037_020baa90(void);
extern void ContinueScene_GetResult(void);

void InitCommHandlerTable(CommHandlerTable *table)
{
    table->open = func_ov037_020bab98;
    table->start = func_ov037_020babbc;
    table->poll = func_ov037_020babe8;
    table->reserved0 = NULL;
    table->isActive = IsPxiChannelActive;
    table->release = ReleasePxiChannel;
    table->apply = func_ov037_020bac50;
    table->reserved1 = NULL;
    table->update = func_ov037_020baa90;
    table->close = ContinueScene_GetResult;
}
