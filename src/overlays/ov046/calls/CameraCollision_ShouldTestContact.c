#include "nitro/types.h"

typedef struct ContactObject {
    u8 pad_00[0x6c];
    int kind;
} ContactObject;

typedef struct CameraContact {
    ContactObject *object;
    int shapeType;
} CameraContact;

typedef struct CameraManager {
    u8 pad_00[0xf4];
    int pathActive;
} CameraManager;

extern s8 func_ov001_02068084(void);
extern BOOL ContainsMatchingEntry(CameraContact *contact, int value);

BOOL CameraCollision_ShouldTestContact(CameraContact *contact, CameraManager *camera)
{
    int kind;

    if (func_ov001_02068084() == 5 && contact->shapeType == 4 && contact->object->kind == 0x1e) {
        return TRUE;
    }
    if (ContainsMatchingEntry(contact, 4)) {
        return FALSE;
    }
    if (contact->shapeType == 4) {
        kind = contact->object->kind;
        if ((kind == 1 && camera->pathActive == 0) || kind == 0x17 || kind == 0x23) {
            return FALSE;
        }
    }
    return TRUE;
}
