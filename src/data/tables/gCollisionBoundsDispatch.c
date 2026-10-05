#include "nitro/types.h"

extern void SphereToBounds(void); /* SphereToBounds */
extern void GetShapeBounds(void); /* GetShapeBounds */
extern void AdjustAabbMargin(void); /* AdjustAabbMargin */
extern void AdjustAabbMarginByField(void); /* AdjustAabbMarginByField */
extern void ShrinkBoundsBySegmentAxis(void); /* ShrinkBoundsBySegmentAxis_02049c48 */
extern void ComputePolygonBounds(void); /* ComputePolygonBounds */

void (*const gCollisionBoundsDispatch[6])(void) = {
    SphereToBounds, /* SphereToBounds */
    GetShapeBounds, /* GetShapeBounds */
    AdjustAabbMargin, /* AdjustAabbMargin */
    AdjustAabbMarginByField, /* AdjustAabbMarginByField */
    ShrinkBoundsBySegmentAxis, /* ShrinkBoundsBySegmentAxis_02049c48 */
    ComputePolygonBounds, /* ComputePolygonBounds */
};
