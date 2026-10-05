#include "nitro/types.h"

extern void SphereToBounds(void); /* SphereToBounds */
extern void func_02049a14(void); /* GetShapeBounds */
extern void AdjustAabbMargin(void); /* AdjustAabbMargin */
extern void AdjustAabbMarginByField(void); /* AdjustAabbMarginByField */
extern void func_02049c5c(void); /* ShrinkBoundsBySegmentAxis_02049c48 */
extern void ComputePolygonBounds(void); /* ComputePolygonBounds */

void (*const gCollisionBoundsDispatch[6])(void) = {
    SphereToBounds, /* SphereToBounds */
    func_02049a14, /* GetShapeBounds */
    AdjustAabbMargin, /* AdjustAabbMargin */
    AdjustAabbMarginByField, /* AdjustAabbMarginByField */
    func_02049c5c, /* ShrinkBoundsBySegmentAxis_02049c48 */
    ComputePolygonBounds, /* ComputePolygonBounds */
};
