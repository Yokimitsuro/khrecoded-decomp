typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct ActorNodeObserved {
    u32 flags_000;
    u16 flags_004;
    u8 unknown_006[0x76];
    void *modelResource_07c;
    u16 halfword_080;
} ActorNodeObserved;

typedef struct ActorObjectObserved {
    u8 unknown_000[0xd18];
    ActorNodeObserved **actorNodeLink_d18;
    u8 unknown_d1c[0x1d8];
    u32 flags_ef4;
    u32 storedParameter_ef8;
    u32 storedParameter_efc;
} ActorObjectObserved;

void ActorObject_SynchronizeConvertedParameter(ActorObjectObserved *actorObject, unsigned short convertedValue)
{
    actorObject->storedParameter_efc = convertedValue;
    actorObject->storedParameter_ef8 = convertedValue;
    ActorNodeObserved *actorNode = *actorObject->actorNodeLink_d18;
    if ((actorNode->flags_000 & 0x20) == 0) {
        actorNode->halfword_080 = convertedValue;
        actorNode->flags_004 |= 0x20;
    }
}
