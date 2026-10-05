#include "nitro/types.h"

extern void func_0203fa4c(void); /* TestSphereAgainstPolygon */
extern void func_0203b55c(void); /* TestBoxAgainstSphere */
extern void func_0203fc5c(void); /* TestBoxAgainstBox */
extern void func_0203fdf4(void); /* TestBoxAgainstCapsule */
extern void func_0203b718(void); /* func */
extern void func_02040038(void); /* func */
extern void func_0203b594(void); /* TestSegmentAgainstSphere */
extern void func_0203b5b0(void); /* TestCapsuleAgainstBox */
extern void func_0204019c(void); /* TestSegmentAgainstSegment */
extern void func_0204055c(void); /* TestCapsuleAgainstCylinder */
extern void func_020405c8(void); /* func */
extern void func_0203c26c(void); /* func */
extern void func_0203b5cc(void); /* TestCapsuleAgainstSphere */
extern void func_0203b578(void); /* TestCylinderAgainstBox */
extern void func_0203b5e8(void); /* TestCylinderAgainstSegment */
extern void func_02041078(void); /* func_02041064 */
extern void func_020410b4(void); /* TestCylinderAgainstCylinder */
extern void func_0203c6d0(void); /* TestCylinderAgainstPolygon */
extern void func_0203b604(void); /* TestCylinderAgainstSphere */
extern void func_0203b620(void); /* TestCapsuleAgainstCapsuleSwapped */
extern void func_0203b63c(void); /* TestCylinderAgainstCylinderSwapped */
extern void func_0203b658(void); /* TestPolygonAgainstSphere */
extern void func_0203b674(void); /* TestPolygonAgainstBox */
extern void func_0203b690(void); /* TestPolygonAgainstSegment */
extern void func_0203b6ac(void); /* TestPolygonAgainstCylinder */
extern void func_020417ac(void); /* TestPolygonAgainstPolygon */
extern void func_0203b6c8(void); /* func */
extern void func_0203f0b0(void); /* TestSphereAgainstBox */
extern void func_0203f2fc(void); /* TestSphereAgainstSegment */
extern void func_0203f624(void); /* TestSphereAgainstCapsule */
extern void func_0203f66c(void); /* TestSphereAgainstCylinder */

void (*const gCollisionTestPairDispatch[31])(void) = {
    func_0203fa4c, /* TestSphereAgainstPolygon */
    func_0203b55c, /* TestBoxAgainstSphere */
    func_0203fc5c, /* TestBoxAgainstBox */
    func_0203fdf4, /* TestBoxAgainstCapsule */
    func_0203b718, /* func */
    func_0203b718, /* func */
    func_02040038, /* func */
    func_0203b594, /* TestSegmentAgainstSphere */
    func_0203b5b0, /* TestCapsuleAgainstBox */
    func_0204019c, /* TestSegmentAgainstSegment */
    func_0204055c, /* TestCapsuleAgainstCylinder */
    func_020405c8, /* func */
    func_0203c26c, /* func */
    func_0203b5cc, /* TestCapsuleAgainstSphere */
    func_0203b578, /* TestCylinderAgainstBox */
    func_0203b5e8, /* TestCylinderAgainstSegment */
    func_02041078, /* func_02041064 */
    func_020410b4, /* TestCylinderAgainstCylinder */
    func_0203c6d0, /* TestCylinderAgainstPolygon */
    func_0203b604, /* TestCylinderAgainstSphere */
    func_0203b578, /* TestCylinderAgainstBox */
    func_0203b620, /* TestCapsuleAgainstCapsuleSwapped */
    func_0203b63c, /* TestCylinderAgainstCylinderSwapped */
    func_020410b4, /* TestCylinderAgainstCylinder */
    func_0203c6d0, /* TestCylinderAgainstPolygon */
    func_0203b658, /* TestPolygonAgainstSphere */
    func_0203b674, /* TestPolygonAgainstBox */
    func_0203b690, /* TestPolygonAgainstSegment */
    func_0203b6ac, /* TestPolygonAgainstCylinder */
    func_0203b6ac, /* TestPolygonAgainstCylinder */
    func_020417ac, /* TestPolygonAgainstPolygon */
};

void (*const gCollisionTestSphereDispatch[5])(void) = {
    func_0203b6c8, /* func */
    func_0203f0b0, /* TestSphereAgainstBox */
    func_0203f2fc, /* TestSphereAgainstSegment */
    func_0203f624, /* TestSphereAgainstCapsule */
    func_0203f66c, /* TestSphereAgainstCylinder */
};
