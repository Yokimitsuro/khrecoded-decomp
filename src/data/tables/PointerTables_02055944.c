#include "nitro/types.h"

extern void func_02042f68(void); /* func */
extern void SweepObbAgainstSphereSwapped(void); /* SweepObbAgainstSphereSwapped */
extern void func_02047b54(void); /* SweepObbAgainstObb */
extern void func_02047dd8(void); /* SweepObbAgainstSegment */
extern void func_020434e4(void); /* func */
extern void func_02048034(void); /* func */
extern void SweepCylinderAgainstSphereSwapped(void); /* SweepCylinderAgainstSphereSwapped */
extern void SweepSegmentAgainstObbSwapped(void); /* SweepSegmentAgainstObbSwapped */
extern void func_02048228(void); /* func */
extern void func_0204847c(void); /* SweepSegmentAgainstCylinder */
extern void func_02048c90(void); /* SweepSegmentAgainstPolygon */
extern void SweepCylinderAgainstInflatedSphereSwapped(void); /* SweepCylinderAgainstInflatedSphereSwapped */
extern void SweepCylinderAgainstBoxSwapped(void); /* SweepCylinderAgainstBoxSwapped */
extern void SweepCylinderAgainstSegmentSwapped(void); /* SweepCylinderAgainstSegmentSwapped */
extern void func_02044928(void); /* func */
extern void func_020449c8(void); /* func */
extern void func_020456d4(void); /* func */
extern void SweepCappedCylinderAgainstSphereSwapped(void); /* SweepCappedCylinderAgainstSphereSwapped */
extern void SweepCylinderAgainstCylinderSwapped(void); /* SweepCylinderAgainstCylinderSwapped */
extern void SweepPolygonAgainstSphereSwapped(void); /* SweepPolygonAgainstSphereSwapped */
extern void SweepSwappedShapes(void); /* SweepSwappedShapes */
extern void func_02041d88(void); /* SweepPolygonAgainstSegmentSwapped */
extern void func_02041df8(void); /* SweepSwappedShapesAlt */
extern void func_02048e2c(void); /* SweepPolygonAgainstPolygon */
extern void func_02041e68(void); /* func */
extern void func_02041f40(void); /* func */
extern void func_0204268c(void); /* func */
extern void func_02042b18(void); /* func */
extern void func_02042b98(void); /* SweepSphereAgainstCappedCylinder */

void (*const gCollisionSweepPairDispatch[31])(void) = {
    func_02042f68, /* func */
    SweepObbAgainstSphereSwapped, /* SweepObbAgainstSphereSwapped */
    func_02047b54, /* SweepObbAgainstObb */
    func_02047dd8, /* SweepObbAgainstSegment */
    func_020434e4, /* func */
    func_020434e4, /* func */
    func_02048034, /* func */
    SweepCylinderAgainstSphereSwapped, /* SweepCylinderAgainstSphereSwapped */
    SweepSegmentAgainstObbSwapped, /* SweepSegmentAgainstObbSwapped */
    func_02048228, /* func */
    func_0204847c, /* SweepSegmentAgainstCylinder */
    func_0204847c, /* SweepSegmentAgainstCylinder */
    func_02048c90, /* SweepSegmentAgainstPolygon */
    SweepCylinderAgainstInflatedSphereSwapped, /* SweepCylinderAgainstInflatedSphereSwapped */
    SweepCylinderAgainstBoxSwapped, /* SweepCylinderAgainstBoxSwapped */
    SweepCylinderAgainstSegmentSwapped, /* SweepCylinderAgainstSegmentSwapped */
    func_02044928, /* func */
    func_020449c8, /* func */
    func_020456d4, /* func */
    SweepCappedCylinderAgainstSphereSwapped, /* SweepCappedCylinderAgainstSphereSwapped */
    SweepCylinderAgainstBoxSwapped, /* SweepCylinderAgainstBoxSwapped */
    SweepCylinderAgainstSegmentSwapped, /* SweepCylinderAgainstSegmentSwapped */
    SweepCylinderAgainstCylinderSwapped, /* SweepCylinderAgainstCylinderSwapped */
    func_020449c8, /* func */
    func_020456d4, /* func */
    SweepPolygonAgainstSphereSwapped, /* SweepPolygonAgainstSphereSwapped */
    SweepSwappedShapes, /* SweepSwappedShapes */
    func_02041d88, /* SweepPolygonAgainstSegmentSwapped */
    func_02041df8, /* SweepSwappedShapesAlt */
    func_02041df8, /* SweepSwappedShapesAlt */
    func_02048e2c, /* SweepPolygonAgainstPolygon */
};

void (*const gCollisionSweepSphereDispatch[5])(void) = {
    func_02041e68, /* func */
    func_02041f40, /* func */
    func_0204268c, /* func */
    func_02042b18, /* func */
    func_02042b98, /* SweepSphereAgainstCappedCylinder */
};
