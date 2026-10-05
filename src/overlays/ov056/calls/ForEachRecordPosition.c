#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef BOOL (*RecordFilter)(s32 recordId, void *userData);
typedef BOOL (*RecordVisitor)(s32 recordId, VecFx32 *position, void *userData);

extern s32 ForwardToActiveServiceWithResult(void);
extern s32 func_ov001_0208796c(s32 recordId);
extern BOOL QueryStageEventPlacement(s32 recordId, u16 cursor, VecFx32 *position, u16 *nextCursor);

void ForEachRecordPosition(RecordFilter filter, RecordVisitor visitor, void *userData)
{
    s32 recordId;
    u16 cursor;
    VecFx32 position;
    BOOL result;

    for (recordId = ForwardToActiveServiceWithResult(); recordId != 0; recordId = func_ov001_0208796c(recordId)) {
        if (filter != NULL) {
            result = filter(recordId, userData);
        } else {
            result = TRUE;
        }
        if (result) {
            cursor = 0;
            do {
                if (QueryStageEventPlacement(recordId, cursor, &position, &cursor)) {
                    if (visitor != NULL) {
                        result = visitor(recordId, &position, userData);
                    } else {
                        result = FALSE;
                    }
                    if (result) {
                        return;
                    }
                }
            } while (cursor != 0);
        }
    }
}
