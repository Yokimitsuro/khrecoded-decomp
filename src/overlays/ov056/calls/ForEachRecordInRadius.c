#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef BOOL (*RecordFilter)(s32 recordId, void *userData);
typedef BOOL (*RecordVisitor)(s32 recordId, VecFx32 *position, void *userData);

typedef struct {
    RecordFilter filter;
    RecordVisitor visitor;
    VecFx32 *center;
    fx32 radius;
    void *userData;
} RecordSearchContext;

extern BOOL InvokeRecordFilter(s32 recordId, RecordSearchContext *context);
extern BOOL func_ov056_020d5154(s32 recordId, VecFx32 *position, RecordSearchContext *context);
extern void func_ov056_020d50d8(void *filter, void *visitor, RecordSearchContext *context);

void ForEachRecordInRadius(RecordFilter filter, RecordVisitor visitor, VecFx32 *center, fx32 radius, void *userData)
{
    RecordSearchContext context;

    context.filter = filter;
    context.visitor = visitor;
    context.center = center;
    context.radius = radius;
    context.userData = userData;
    func_ov056_020d50d8(InvokeRecordFilter, func_ov056_020d5154, &context);
}
