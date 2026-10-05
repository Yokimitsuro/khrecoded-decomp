#include "nitro/types.h"

extern void func_0203fa4c(void); /* TestSphereAgainstPolygon */
extern void TestBoxAgainstSphere(void); /* TestBoxAgainstSphere */
extern void func_0203fc5c(void); /* TestBoxAgainstBox */
extern void func_0203fdf4(void); /* TestBoxAgainstCapsule */
extern void func_0203b718(void); /* func */
extern void func_02040038(void); /* func */
extern void TestSegmentAgainstSphere(void); /* TestSegmentAgainstSphere */
extern void TestCapsuleAgainstBox(void); /* TestCapsuleAgainstBox */
extern void func_0204019c(void); /* TestSegmentAgainstSegment */
extern void func_0204055c(void); /* TestCapsuleAgainstCylinder */
extern void func_020405c8(void); /* func */
extern void func_0203c26c(void); /* func */
extern void TestCapsuleAgainstSphere(void); /* TestCapsuleAgainstSphere */
extern void TestCylinderAgainstBox(void); /* TestCylinderAgainstBox */
extern void TestCylinderAgainstSegment(void); /* TestCylinderAgainstSegment */
extern void func_02041078(void); /* func_02041064 */
extern void func_020410b4(void); /* TestCylinderAgainstCylinder */
extern void func_0203c6d0(void); /* TestCylinderAgainstPolygon */
extern void TestCylinderAgainstSphere(void); /* TestCylinderAgainstSphere */
extern void TestCapsuleAgainstCapsuleSwapped(void); /* TestCapsuleAgainstCapsuleSwapped */
extern void TestCylinderAgainstCylinderSwapped(void); /* TestCylinderAgainstCylinderSwapped */
extern void TestPolygonAgainstSphere(void); /* TestPolygonAgainstSphere */
extern void TestPolygonAgainstBox(void); /* TestPolygonAgainstBox */
extern void TestPolygonAgainstSegment(void); /* TestPolygonAgainstSegment */
extern void TestPolygonAgainstCylinder(void); /* TestPolygonAgainstCylinder */
extern void func_020417ac(void); /* TestPolygonAgainstPolygon */
extern void func_0203b6c8(void); /* func */
extern void func_0203f0b0(void); /* TestSphereAgainstBox */
extern void func_0203f2fc(void); /* TestSphereAgainstSegment */
extern void func_0203f624(void); /* TestSphereAgainstCapsule */
extern void func_0203f66c(void); /* TestSphereAgainstCylinder */

void (*const gCollisionTestPairDispatch[31])(void) = {
    func_0203fa4c, /* TestSphereAgainstPolygon */
    TestBoxAgainstSphere, /* TestBoxAgainstSphere */
    func_0203fc5c, /* TestBoxAgainstBox */
    func_0203fdf4, /* TestBoxAgainstCapsule */
    func_0203b718, /* func */
    func_0203b718, /* func */
    func_02040038, /* func */
    TestSegmentAgainstSphere, /* TestSegmentAgainstSphere */
    TestCapsuleAgainstBox, /* TestCapsuleAgainstBox */
    func_0204019c, /* TestSegmentAgainstSegment */
    func_0204055c, /* TestCapsuleAgainstCylinder */
    func_020405c8, /* func */
    func_0203c26c, /* func */
    TestCapsuleAgainstSphere, /* TestCapsuleAgainstSphere */
    TestCylinderAgainstBox, /* TestCylinderAgainstBox */
    TestCylinderAgainstSegment, /* TestCylinderAgainstSegment */
    func_02041078, /* func_02041064 */
    func_020410b4, /* TestCylinderAgainstCylinder */
    func_0203c6d0, /* TestCylinderAgainstPolygon */
    TestCylinderAgainstSphere, /* TestCylinderAgainstSphere */
    TestCylinderAgainstBox, /* TestCylinderAgainstBox */
    TestCapsuleAgainstCapsuleSwapped, /* TestCapsuleAgainstCapsuleSwapped */
    TestCylinderAgainstCylinderSwapped, /* TestCylinderAgainstCylinderSwapped */
    func_020410b4, /* TestCylinderAgainstCylinder */
    func_0203c6d0, /* TestCylinderAgainstPolygon */
    TestPolygonAgainstSphere, /* TestPolygonAgainstSphere */
    TestPolygonAgainstBox, /* TestPolygonAgainstBox */
    TestPolygonAgainstSegment, /* TestPolygonAgainstSegment */
    TestPolygonAgainstCylinder, /* TestPolygonAgainstCylinder */
    TestPolygonAgainstCylinder, /* TestPolygonAgainstCylinder */
    func_020417ac, /* TestPolygonAgainstPolygon */
};

void (*const gCollisionTestSphereDispatch[5])(void) = {
    func_0203b6c8, /* func */
    func_0203f0b0, /* TestSphereAgainstBox */
    func_0203f2fc, /* TestSphereAgainstSegment */
    func_0203f624, /* TestSphereAgainstCapsule */
    func_0203f66c, /* TestSphereAgainstCylinder */
};
