/* Stores the callback later used by the overlay-object creation path. */
typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);

typedef struct OverlayObjectFactoryStateObserved {
    unsigned int unknown_000;
    OverlayObjectFactory currentFactory_004;
} OverlayObjectFactoryStateObserved;

extern OverlayObjectFactoryStateObserved data_ov001_020a04bc;

void SetOverlayObjectFactory(OverlayObjectFactory factory)
{
    data_ov001_020a04bc.currentFactory_004 = factory;
}
