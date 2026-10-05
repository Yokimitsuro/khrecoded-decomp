#include "nitro/types.h"

extern void TestSphereAgainstPolygon(void); /* TestSphereAgainstPolygon */
extern void TestBoxAgainstSphere(void); /* TestBoxAgainstSphere */
extern void TestBoxAgainstBox(void); /* TestBoxAgainstBox */
extern void TestBoxAgainstCapsule(void); /* TestBoxAgainstCapsule */
extern void func_0203b718(void); /* func */
extern void func_02040038(void); /* func */
extern void TestSegmentAgainstSphere(void); /* TestSegmentAgainstSphere */
extern void TestCapsuleAgainstBox(void); /* TestCapsuleAgainstBox */
extern void TestSegmentAgainstSegment(void); /* TestSegmentAgainstSegment */
extern void TestCapsuleAgainstCylinder(void); /* TestCapsuleAgainstCylinder */
extern void func_020405c8(void); /* func */
extern void func_0203c26c(void); /* func */
extern void TestCapsuleAgainstSphere(void); /* TestCapsuleAgainstSphere */
extern void TestCylinderAgainstBox(void); /* TestCylinderAgainstBox */
extern void TestCylinderAgainstSegment(void); /* TestCylinderAgainstSegment */
extern void func_02041078(void); /* func_02041064 */
extern void TestCylinderAgainstCylinder(void); /* TestCylinderAgainstCylinder */
extern void TestCylinderAgainstPolygon(void); /* TestCylinderAgainstPolygon */
extern void TestCylinderAgainstSphere(void); /* TestCylinderAgainstSphere */
extern void TestCapsuleAgainstCapsuleSwapped(void); /* TestCapsuleAgainstCapsuleSwapped */
extern void TestCylinderAgainstCylinderSwapped(void); /* TestCylinderAgainstCylinderSwapped */
extern void TestPolygonAgainstSphere(void); /* TestPolygonAgainstSphere */
extern void TestPolygonAgainstBox(void); /* TestPolygonAgainstBox */
extern void TestPolygonAgainstSegment(void); /* TestPolygonAgainstSegment */
extern void TestPolygonAgainstCylinder(void); /* TestPolygonAgainstCylinder */
extern void TestPolygonAgainstPolygon(void); /* TestPolygonAgainstPolygon */
extern void func_0203b6c8(void); /* func */
extern void TestSphereAgainstBox(void); /* TestSphereAgainstBox */
extern void TestSphereAgainstSegment(void); /* TestSphereAgainstSegment */
extern void TestSphereAgainstCapsule(void); /* TestSphereAgainstCapsule */
extern void TestSphereAgainstCylinder(void); /* TestSphereAgainstCylinder */

void (*const gCollisionTestPairDispatch[31])(void) = {
    TestSphereAgainstPolygon, /* TestSphereAgainstPolygon */
    TestBoxAgainstSphere, /* TestBoxAgainstSphere */
    TestBoxAgainstBox, /* TestBoxAgainstBox */
    TestBoxAgainstCapsule, /* TestBoxAgainstCapsule */
    func_0203b718, /* func */
    func_0203b718, /* func */
    func_02040038, /* func */
    TestSegmentAgainstSphere, /* TestSegmentAgainstSphere */
    TestCapsuleAgainstBox, /* TestCapsuleAgainstBox */
    TestSegmentAgainstSegment, /* TestSegmentAgainstSegment */
    TestCapsuleAgainstCylinder, /* TestCapsuleAgainstCylinder */
    func_020405c8, /* func */
    func_0203c26c, /* func */
    TestCapsuleAgainstSphere, /* TestCapsuleAgainstSphere */
    TestCylinderAgainstBox, /* TestCylinderAgainstBox */
    TestCylinderAgainstSegment, /* TestCylinderAgainstSegment */
    func_02041078, /* func_02041064 */
    TestCylinderAgainstCylinder, /* TestCylinderAgainstCylinder */
    TestCylinderAgainstPolygon, /* TestCylinderAgainstPolygon */
    TestCylinderAgainstSphere, /* TestCylinderAgainstSphere */
    TestCylinderAgainstBox, /* TestCylinderAgainstBox */
    TestCapsuleAgainstCapsuleSwapped, /* TestCapsuleAgainstCapsuleSwapped */
    TestCylinderAgainstCylinderSwapped, /* TestCylinderAgainstCylinderSwapped */
    TestCylinderAgainstCylinder, /* TestCylinderAgainstCylinder */
    TestCylinderAgainstPolygon, /* TestCylinderAgainstPolygon */
    TestPolygonAgainstSphere, /* TestPolygonAgainstSphere */
    TestPolygonAgainstBox, /* TestPolygonAgainstBox */
    TestPolygonAgainstSegment, /* TestPolygonAgainstSegment */
    TestPolygonAgainstCylinder, /* TestPolygonAgainstCylinder */
    TestPolygonAgainstCylinder, /* TestPolygonAgainstCylinder */
    TestPolygonAgainstPolygon, /* TestPolygonAgainstPolygon */
};

void (*const gCollisionTestDispatch[5])(void) = {
    func_0203b6c8, /* func */
    TestSphereAgainstBox, /* TestSphereAgainstBox */
    TestSphereAgainstSegment, /* TestSphereAgainstSegment */
    TestSphereAgainstCapsule, /* TestSphereAgainstCapsule */
    TestSphereAgainstCylinder, /* TestSphereAgainstCylinder */
};
