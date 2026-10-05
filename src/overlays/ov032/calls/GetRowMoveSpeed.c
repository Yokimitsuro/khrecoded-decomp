#include "src/overlays/ov032/row_definition.h"

u32 GetRowMoveSpeed(RowOwner *owner, s32 index)
{
    return GetRowDefinition(owner, index)->moveSpeed;
}
