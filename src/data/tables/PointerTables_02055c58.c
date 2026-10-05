#include "nitro/types.h"

extern u8 sFrmTexVramRegion4[];
extern u8 sFrmTexVramRegion3[];
extern u8 sFrmTexVramRegions[];
extern u8 sFrmTexVramRegion2[];
extern u8 sFrmTexVramRegion1[];
extern void Gfd_DefaultFreePlttVram(void); /* func */

void *sFrmTexVramNormalRegions[5] = {
    sFrmTexVramRegion4, /* sFrmTexVramRegion4 */
    sFrmTexVramRegion3, /* sFrmTexVramRegion3 */
    sFrmTexVramRegions, /* sFrmTexVramRegions */
    sFrmTexVramRegion2, /* sFrmTexVramRegion2 */
    sFrmTexVramRegion1, /* sFrmTexVramRegion1 */
};

void *sFrmTexVramRegionOrder[2] = {
    sFrmTexVramRegions, /* sFrmTexVramRegions */
    sFrmTexVramRegion3, /* sFrmTexVramRegion3 */
};

void (*sDefaultFreePlttVramFunc[1])(void) = {
    Gfd_DefaultFreePlttVram, /* func */
};
