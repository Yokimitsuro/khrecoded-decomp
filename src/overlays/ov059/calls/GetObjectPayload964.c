#include "nitro/types.h"

typedef struct ObjectPayloadOwner {
    u8 pad_000[0x964];
    u8 payload[1];
} ObjectPayloadOwner;

void *GetObjectPayload964(ObjectPayloadOwner *object)
{
    return object->payload;
}
