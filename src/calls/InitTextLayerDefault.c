#include "nitro/types.h"

typedef struct NNSG2dFont NNSG2dFont;
typedef struct TextLayer TextLayer;
typedef struct TextFrame TextFrame;

extern BOOL func_020012dc(TextLayer *obj, int layer, u16 *screenBase, NNSG2dFont *font, TextFrame *frame, BOOL fillMap, int alignFromEnd);

BOOL InitTextLayerDefault(TextLayer *obj, int layer, NNSG2dFont *font, TextFrame *frame)
{
    return func_020012dc(obj, layer, NULL, font, frame, TRUE, 0);
}
