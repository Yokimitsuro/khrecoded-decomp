#include "nitro/types.h"

extern void func_01ffad00(void); /* func */
extern void func_01ffae7c(void); /* func */
extern void func_01ffa624(void); /* func */
extern void func_01ffa73c(void); /* func */

void (*gMaterialAnimationDispatch[4])(void) = {
    func_01ffad00, /* func */
    NULL,
    func_01ffae7c, /* func */
    NULL,
};

void (*gJointAnimationNodeDispatch[3])(void) = {
    func_01ffa624, /* func */
    func_01ffa73c, /* func */
    NULL,
};
