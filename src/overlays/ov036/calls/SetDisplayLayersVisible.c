#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x20];
    u32 layerMask;
} LayerConfig;

#define REG_DISPCNT (*(volatile u32 *)0x04000000)

void SetDisplayLayersVisible(LayerConfig *config, BOOL enable) {
    u32 visibleLayers;
    u32 currentLayers = REG_DISPCNT & 0x1f00;
    if (enable) {
        visibleLayers = config->layerMask | (currentLayers >> 8);
    } else {
        visibleLayers = ~config->layerMask & (currentLayers >> 8);
    }
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | (visibleLayers << 8);
}
