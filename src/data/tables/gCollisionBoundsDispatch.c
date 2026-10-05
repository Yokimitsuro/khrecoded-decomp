#include "nitro/types.h"

extern void func_020499d8(void); /* SphereToBounds */
extern void func_02049a14(void); /* GetShapeBounds */
extern void func_02049c04(void); /* AdjustAabbMargin */
extern void func_02049c30(void); /* AdjustAabbMarginByField */
extern void func_02049c5c(void); /* ShrinkBoundsBySegmentAxis_02049c48 */
extern void ComputePolygonBounds(void); /* ComputePolygonBounds */

void (*const gCollisionBoundsDispatch[6])(void) = {
    func_020499d8, /* SphereToBounds */
    func_02049a14, /* GetShapeBounds */
    func_02049c04, /* AdjustAabbMargin */
    func_02049c30, /* AdjustAabbMarginByField */
    func_02049c5c, /* ShrinkBoundsBySegmentAxis_02049c48 */
    ComputePolygonBounds, /* ComputePolygonBounds */
};
