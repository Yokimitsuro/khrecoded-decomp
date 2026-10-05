#include "nitro/types.h"

extern u8 data_ov002_0206c470;

extern void AppendProfileHistory(u32 value);
extern void RemoveContextSlot(u32 value);
extern void ImportSlotConfigFlags(u32 value);
extern void SetContextConfigByte1ac8(u32 value);
extern void SetContextConfigFlag1ac8(u32 value);
extern void SetContextConfigNibble(u32 value);
extern void SetClampedPercentValue(u32 value);
extern void func_ov002_02067538(u32 value);
extern void func_ov002_02067564(u32 value);
extern void SetTierMaskLowBit(u32 value, u32 extra);
extern void SetTierMaskHighBit(u32 value, u32 extra);
extern void func_ov002_020678cc(u32 value, void *buffer);
extern void func_ov002_020678fc(u32 value, void *buffer);
extern void SetSlotConfigFlag38(u32 value, u32 extra);
extern void SetSlotConfigFlag38_02067840(u32 value, u32 extra);
extern void SetSlotConfigFlag38_02067870(u32 value, u32 extra);
extern void func_ov002_0206793c(u32 value, u32 extra, void *buffer);
extern void WriteGlobalPackedFlag(int flagIndex, u32 value);
extern void SetContextConfigByte1ba2(u32 value);
extern void SetContextConfigFlag1ad0(u32 value);
extern void func_ov002_020679ac(u32 value, u32 extra);
extern void func_ov002_02067974(u32 value, u32 extra, void *buffer);

extern void LoadStoredPlayerCard(void *buffer);
extern u32 GetContextSlotCount(void);
extern u32 IsContextSlotFlagSet(u32 value);
extern void ExportSlotConfigFlags(u32 value);
extern u32 GetContextConfigByte1ac8(void);
extern u32 GetContextConfigFlag1ac8(void);
extern u32 GetContextConfigNibble1ac8(void);
extern u32 func_ov002_02067524(void);
extern u32 GetContextConfigField1acc(void);
extern u32 IsTierMaskBitClear(u32 value);
extern u32 IsTierMaskBitSet(u32 value);
extern u32 IsSlotConfigFlagClear(u32 value);
extern u32 IsContextSlotFlag19Set(u32 value);
extern u32 func_ov002_020679fc(int flagIndex);
extern u32 GetContextConfigByte1ba2(void);
extern u32 GetContextConfigFlag1ad0(void);

u32 DispatchContextCommand(u32 command, u32 value, u32 extra, void *buffer)
{
    if (command & 0x80000000) {
        data_ov002_0206c470 = 1;
        switch (command) {
        case 0x80000001:
            AppendProfileHistory(value);
            break;
        case 0x80000002:
            RemoveContextSlot(value);
            break;
        case 0x80000003:
            ImportSlotConfigFlags(value);
            break;
        case 0x80000004:
            SetContextConfigByte1ac8(value);
            break;
        case 0x80000005:
            SetContextConfigFlag1ac8(value);
            break;
        case 0x80000006:
            SetContextConfigNibble(value);
            break;
        case 0x80000007:
            SetClampedPercentValue(value);
            break;
        case 0x80000008:
            func_ov002_02067538(value);
            break;
        case 0x80000009:
            func_ov002_02067564(value);
            break;
        case 0x8000000a:
            SetTierMaskLowBit(value, extra);
            break;
        case 0x8000000b:
            SetTierMaskHighBit(value, extra);
            break;
        case 0x8000000c:
            func_ov002_020678cc(value, buffer);
            break;
        case 0x8000000d:
            func_ov002_020678fc(value, buffer);
            break;
        case 0x8000000e:
            SetSlotConfigFlag38(value, extra);
            break;
        case 0x8000000f:
            SetSlotConfigFlag38_02067840(value, extra);
            break;
        case 0x80000010:
            SetSlotConfigFlag38_02067870(value, extra);
            break;
        case 0x80000011:
            func_ov002_0206793c(value, extra, buffer);
            break;
        case 0x80000012:
            WriteGlobalPackedFlag(0x48, value);
            break;
        case 0x80000013:
            WriteGlobalPackedFlag(0x47, value);
            break;
        case 0x80000014:
            WriteGlobalPackedFlag(0x4c, value);
            break;
        case 0x80000015:
            WriteGlobalPackedFlag(0xb9, value);
            break;
        case 0x80000016:
            SetContextConfigByte1ba2(value);
            break;
        case 0x80000017:
            SetContextConfigFlag1ad0(value);
            break;
        case 0x80000018:
            func_ov002_020679ac(value, extra);
            break;
        case 0x80000019:
            func_ov002_02067974(value, extra, buffer);
            break;
        }
    } else {
        switch (command) {
        case 0:
            LoadStoredPlayerCard(buffer);
            break;
        case 1:
            return GetContextSlotCount();
        case 2:
            return IsContextSlotFlagSet(value);
        case 3:
            ExportSlotConfigFlags(value);
            break;
        case 4:
            return GetContextConfigByte1ac8();
        case 5:
            return GetContextConfigFlag1ac8();
        case 6:
            return GetContextConfigNibble1ac8();
        case 7:
            return func_ov002_02067524();
        case 8:
            return GetContextConfigField1acc();
        case 9:
            return IsTierMaskBitClear(value);
        case 10:
            return IsTierMaskBitSet(value);
        case 11:
            return IsSlotConfigFlagClear(value);
        case 12:
            return IsContextSlotFlag19Set(value);
        case 13:
            return func_ov002_020679fc(0x48);
        case 14:
            return func_ov002_020679fc(0x47);
        case 15:
            return func_ov002_020679fc(0x4c);
        case 16:
            return func_ov002_020679fc(0xb9);
        case 17:
            return GetContextConfigByte1ba2();
        case 18:
            return GetContextConfigFlag1ad0();
        }
    }
    return 0;
}
