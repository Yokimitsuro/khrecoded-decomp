#include "nitro/types.h"

extern u8 sMain_Ja_02055ff4[];
extern u8 sMain_En_02055fe0[];
extern u8 sMain_Fr_02055fec[];
extern u8 sMain_De_02055fe8[];
extern u8 sMain_It_02055fe4[];
extern u8 sMain_Es_02055ff0[];
extern u8 sMain_Zh_02055fdc[];

void *gLanguageCodeTable[7] = {
    sMain_Ja_02055ff4, /* sMain_Ja_02055ff4 */
    sMain_En_02055fe0, /* sMain_En_02055fe0 */
    sMain_Fr_02055fec, /* sMain_Fr_02055fec */
    sMain_De_02055fe8, /* sMain_De_02055fe8 */
    sMain_It_02055fe4, /* sMain_It_02055fe4 */
    sMain_Es_02055ff0, /* sMain_Es_02055ff0 */
    sMain_Zh_02055fdc, /* sMain_Zh_02055fdc */
};
