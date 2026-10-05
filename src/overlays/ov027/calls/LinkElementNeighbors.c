#include "nitro/types.h"

#define NO_NEIGHBOR_ID (-0x7FFFFFFF)

typedef struct ContainerElement {
    u8 pad_00[0x94];
    u32 flags;
    struct ContainerElement *neighbors[4];
} ContainerElement;

typedef struct ElementDesc {
    int id;
    u8 pad_04[0x3C];
    int neighborIds[4];
} ElementDesc;

extern ContainerElement *FindWidgetById(void *container, int id);

void LinkElementNeighbors(void *container, ElementDesc *desc) {
    ContainerElement *element;
    int neighborId;

    element = FindWidgetById(container, desc->id);

    neighborId = desc->neighborIds[0];
    if (neighborId < 0) {
        neighborId = -neighborId;
    }
    element->neighbors[0] = FindWidgetById(container, neighborId);
    if (desc->neighborIds[0] != NO_NEIGHBOR_ID && desc->neighborIds[0] < 0) {
        element->flags |= 0x10;
    }

    neighborId = desc->neighborIds[1];
    if (neighborId < 0) {
        neighborId = -neighborId;
    }
    element->neighbors[1] = FindWidgetById(container, neighborId);
    if (desc->neighborIds[1] != NO_NEIGHBOR_ID && desc->neighborIds[1] < 0) {
        element->flags |= 0x20;
    }

    neighborId = desc->neighborIds[2];
    if (neighborId < 0) {
        neighborId = -neighborId;
    }
    element->neighbors[2] = FindWidgetById(container, neighborId);
    if (desc->neighborIds[2] != NO_NEIGHBOR_ID && desc->neighborIds[2] < 0) {
        element->flags |= 0x40;
    }

    neighborId = desc->neighborIds[3];
    if (neighborId < 0) {
        neighborId = -neighborId;
    }
    element->neighbors[3] = FindWidgetById(container, neighborId);
    if (desc->neighborIds[3] != NO_NEIGHBOR_ID && desc->neighborIds[3] < 0) {
        element->flags |= 0x80;
    }
}
