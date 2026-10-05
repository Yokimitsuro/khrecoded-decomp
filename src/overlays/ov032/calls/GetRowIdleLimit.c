#include "src/overlays/ov032/row_definition.h"

s32 GetRowIdleLimit(RowOwner *owner, s32 index)
{
    return (s16)GetRowDefinition(owner, index)->idleLimit;
}
