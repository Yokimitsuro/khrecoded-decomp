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


void ClearPackedField(PackedFields *fields, int fieldIndex, int matchIndex)
{
    switch (fieldIndex) {
    case 0: fields->field0 = 0; break;
    case 1: fields->field1 = 0; break;
    case 2: fields->field2 = 0; break;
    case 3: fields->field3 = 0; break;
    case 4: fields->field4 = 0; break;
    case 5: fields->field5 = 0; break;
    case 6: fields->field6 = 0; break;
    case 7: fields->field7 = 0; break;
    case 8: fields->field8 = 0; break;
    case 9: fields->field9 = 0; break;
    case 10: fields->field10 = 0; break;
    case 11: fields->field11 = 0; break;
    case 12: fields->field12 = 0; break;
    case 13: fields->field13 = 0; break;
    case 14: fields->field14 = 0; break;
    case 15: fields->field15 = 0; break;
    case 16:
        if (matchIndex < 0) {
            fields->field16 = 0;
        } else if (matchIndex + 1 == fields->field16) {
            fields->field16 = 0;
        } else if (matchIndex + 1 == fields->field20) {
            fields->field20 = 0;
        } else if (matchIndex + 1 == fields->field21) {
            fields->field21 = 0;
        }
        break;
    case 17: fields->field17 = 0; break;
    case 19: fields->field19 = 0; break;
    case 20: fields->field20 = 0; break;
    case 21: fields->field21 = 0; break;
    }
}
