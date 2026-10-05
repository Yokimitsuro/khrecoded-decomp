#include "src/overlays/ov032/row_definition.h"

s32 GetRowStepLimit(RowOwner *owner, s32 index)
{
    return GetRowDefinition(owner, index)->stepLimit;
}
