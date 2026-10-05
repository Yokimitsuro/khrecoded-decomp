#include "src/overlays/ov032/row_definition.h"

RowDefinition *GetRowDefinition(RowOwner *owner, s32 index)
{
    return &owner->definitions[owner->rows[index].definitionIndex];
}
