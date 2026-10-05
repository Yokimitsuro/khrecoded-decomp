#include "nitro/types.h"

typedef struct PackedFields {
    u32 field6 : 5;
    u32 field17 : 5;
    u32 field12 : 6;
    u32 field20 : 7;
    u32 field21 : 7;
    u32 pad0 : 2;
    u32 field0 : 4;
    u32 field1 : 4;
    u32 field3 : 8;
    u32 field4 : 5;
    u32 field5 : 5;
    u32 field2 : 6;
    u32 field7 : 7;
    u32 field8 : 7;
    u32 field9 : 7;
    u32 field10 : 7;
    u32 field15 : 4;
    u32 field11 : 7;
    u32 field16 : 7;
    u32 field13 : 6;
    u32 field19 : 5;
    u32 field14 : 5;
    u32 pad3 : 2;
} PackedFields;

extern PackedFields *func_ov002_02066fc8(void);

int GetPackedField(PackedFields *fields, int fieldIndex, int matchIndex)
{
    u32 value = 0;
    if (fields == NULL) {
        fields = func_ov002_02066fc8();
    }
    switch (fieldIndex) {
    case 0: value = fields->field0; break;
    case 1: value = fields->field1; break;
    case 2: value = fields->field2; break;
    case 3: value = fields->field3; break;
    case 4: value = fields->field4; break;
    case 5: value = fields->field5; break;
    case 6: value = fields->field6; break;
    case 7: value = fields->field7; break;
    case 8: value = fields->field8; break;
    case 9: value = fields->field9; break;
    case 10: value = fields->field10; break;
    case 11: value = fields->field11; break;
    case 12: value = fields->field12; break;
    case 13: value = fields->field13; break;
    case 14: value = fields->field14; break;
    case 15: value = fields->field15; break;
    case 16:
        if (matchIndex < 0) {
            value = fields->field16;
        } else if (matchIndex + 1 == fields->field16) {
            value = matchIndex + 1;
        } else if (matchIndex + 1 == fields->field20) {
            value = matchIndex + 1;
        } else if (matchIndex + 1 == fields->field21) {
            value = matchIndex + 1;
        }
        break;
    case 17: value = fields->field17; break;
    case 19: value = fields->field19; break;
    case 20: value = fields->field20; break;
    case 21: value = fields->field21; break;
    }
    return value - 1;
}
