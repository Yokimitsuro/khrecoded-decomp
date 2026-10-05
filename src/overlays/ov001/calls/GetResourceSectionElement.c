#include "nitro/types.h"

typedef struct ResourceSection {
    u32 unk_00;
    u32 count;
    u32 stride;
    u8 *data;
} ResourceSection;

typedef struct ResourceHeader {
    u32 unk_00;
    u32 unk_04;
    ResourceSection *sections;
} ResourceHeader;

typedef struct Resource {
    u32 unk_00;
    ResourceHeader *header;
} Resource;

static inline u32 GetResourceSectionCount(Resource *resource, int index)
{
    if (resource == NULL) {
        return 0;
    }
    if (resource->header == NULL) {
        return 0;
    }
    if (index < 0) {
        return 0;
    }
    if (index >= 19) {
        return 0;
    }
    return resource->header->sections[index].count;
}

void *GetResourceSectionElement(Resource *resource, int index, u32 element)
{
    ResourceHeader *header;
    ResourceSection *section;
    u32 count;
    u8 *data;

    if (resource == NULL) {
        return NULL;
    }
    header = resource->header;
    if (header == NULL) {
        return NULL;
    }
    if (index < 0) {
        return NULL;
    }
    if (index >= 19) {
        return NULL;
    }
    count = GetResourceSectionCount(resource, index);
    section = &header->sections[index];
    data = section->data;
    if (count == 0) {
        return NULL;
    }
    if (element >= count) {
        return NULL;
    }
    return data + element * section->stride;
}
