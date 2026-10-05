#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    int eventId;
    int defaultValue;
    u8 pad_10[4];
    int altValue;
    int secondAltValue;
    u8 pad_1c[0x20];
} EventVariant;

typedef struct {
    u8 pad_00[0xac];
    EventVariant *variants;
    u8 pad_b0[0x1c];
    int variantCount;
} EventVariantTable;

typedef struct {
    u32 unk0;
    EventVariantTable *table;
} EventVariantHolder;

extern EventVariantHolder data_ov001_020a04d0;
extern BOOL IsFieldFlag13OrSessionFlagSet(void);
extern BOOL IsFieldFlag8Set(void);

int ResolveEventVariant(int eventId)
{
    EventVariantTable *table = data_ov001_020a04d0.table;
    EventVariant *variant;
    int i;
    int result;

    for (i = 0; i < table->variantCount; i++) {
        variant = &table->variants[i];
        if (variant->eventId == eventId) {
            break;
        }
    }
    if (i == table->variantCount) {
        return -1;
    }
    if (IsFieldFlag13OrSessionFlagSet()) {
        result = variant->altValue;
        if (result == -1) {
            result = variant->secondAltValue;
            if (result == -1) {
                return variant->defaultValue;
            }
        }
    } else if (IsFieldFlag8Set()) {
        result = variant->altValue;
        if (result == -1) {
            return variant->defaultValue;
        }
    } else {
        result = variant->defaultValue;
    }
    return result;
}
