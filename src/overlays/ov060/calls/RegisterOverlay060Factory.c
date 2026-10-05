typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay060Object(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void RegisterOverlay060Factory(void)
{
    SetOverlayObjectFactory(CreateOverlay060Object);
}
