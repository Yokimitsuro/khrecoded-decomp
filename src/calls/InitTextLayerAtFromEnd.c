#include "nitro/types.h"

typedef struct NNSG2dFont NNSG2dFont;
typedef struct TextLayer TextLayer;
typedef struct TextFrame TextFrame;

extern BOOL InitTextLayer(TextLayer *obj, int layer, u16 *screenBase, NNSG2dFont *font, TextFrame *frame, BOOL fillMap, int alignFromEnd);

BOOL InitTextLayerAtFromEnd(TextLayer *obj, int layer, u16 *screenBase, NNSG2dFont *font, TextFrame *frame)
{
    return InitTextLayer(obj, layer, screenBase, font, frame, screenBase != NULL, 1);
}
