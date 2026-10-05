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
extern BOOL VisitRecordInRadius(s32 recordId, VecFx32 *position, RecordSearchContext *context);
extern void ForEachRecordPosition(void *filter, void *visitor, RecordSearchContext *context);

void ForEachRecordInRadius(RecordFilter filter, RecordVisitor visitor, VecFx32 *center, fx32 radius, void *userData)
{
    RecordSearchContext context;

    context.filter = filter;
    context.visitor = visitor;
    context.center = center;
    context.radius = radius;
    context.userData = userData;
    ForEachRecordPosition(InvokeRecordFilter, VisitRecordInRadius, &context);
}
