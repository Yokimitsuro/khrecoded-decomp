#include "nitro/types.h"

typedef struct Ov081State Ov081State;

extern Ov081State *data_ov081_020c5da0;
extern void func_ov081_020c5a94(Ov081State *state, BOOL forward);
extern void func_ov081_020c5660(void *obj);
extern void func_ov081_020c4e08(void *obj);
extern void *func_ov081_020c544c(void);
extern void func_ov081_020c56c8(Ov081State *state, void *list);

void AdvanceListAndRedraw(void)
{
    Ov081State *state;

    func_ov081_020c5a94(data_ov081_020c5da0, TRUE);
    func_ov081_020c5660(data_ov081_020c5da0);
    state = data_ov081_020c5da0;
    func_ov081_020c56c8(state, func_ov081_020c544c());
    func_ov081_020c5660(state);
    func_ov081_020c4e08(data_ov081_020c5da0);
}
