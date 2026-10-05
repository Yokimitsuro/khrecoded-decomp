#include "nitro/types.h"

typedef struct NNSG2dFont NNSG2dFont;
typedef struct TextLayer TextLayer;
typedef struct TextFrame TextFrame;

extern BOOL func_020012dc(TextLayer *obj, int layer, u16 *screenBase, NNSG2dFont *font, TextFrame *frame, BOOL fillMap, int alignFromEnd);

BOOL InitTextLayerAt(TextLayer *obj, int layer, u16 *screenBase, NNSG2dFont *font, TextFrame *frame)
{
    return func_020012dc(obj, layer, screenBase, font, frame, screenBase != NULL, 0);
}
