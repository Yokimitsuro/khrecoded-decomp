typedef unsigned long u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct OSOwnerInfo {
    u8 language;
    u8 favoriteColor;
    struct {
        u8 month;
        u8 day;
    } birthday;
    u16 nickName[11];
    u16 nickNameLength;
    u16 comment[27];
    u16 commentLength;
} OSOwnerInfo;

const u8 bad_mac_addr[6] = { 0xff, 0xf6, 0x40, 0xff, 0xff, 0xce };

extern void OS_GetMacAddress(u8 *address);
extern void OS_GetOwnerInfo(OSOwnerInfo *info);

static inline u32 testMACOwner(u32 passValue, u32 failValue)
{
    u8 address[6];
    OSOwnerInfo owner;
    int i;
    u32 result;

    OS_GetMacAddress(address);
    for (i = 0; i < 6; i++) {
        if (bad_mac_addr[i] != (address[i] ^ 0xff)) {
            break;
        }
    }

    OS_GetOwnerInfo(&owner);
    if (i == 6 && owner.birthday.month == 1 && owner.birthday.day == 1 && owner.nickNameLength == 0) {
        result = failValue;
        goto exit;
    }

    for (i = 0; i < 6; i++) {
        if (address[i] != 0) {
            result = passValue;
            goto exit;
        }
    }

    result = failValue;
exit:
    return result;
}

u32 MACOwner_IsBad(void)
{
    return testMACOwner(241, 251) * 197;
}