#include "libs/nitro/card/card_rom_internal.h"

extern void MI_CpuFill8(void *destination, u8 value, u32 length);


#define CARD_BACKUP_TYPE_NOT_USE 0
#define CARD_BACKUP_TYPE_DEVICE_SHIFT 0
#define CARD_BACKUP_TYPE_DEVICE_MASK 0xff
#define CARD_BACKUP_TYPE_DEVICE_EEPROM 1
#define CARD_BACKUP_TYPE_DEVICE_FLASH 2
#define CARD_BACKUP_TYPE_DEVICE_FRAM 3
#define CARD_BACKUP_TYPE_SIZEBIT_SHIFT 8
#define CARD_BACKUP_TYPE_SIZEBIT_MASK 0xff
#define CARD_BACKUP_TYPE_VENDOR_SHIFT 16
#define CARD_BACKUP_TYPE_VENDOR_MASK 0xff

#define CARD_BACKUP_CAPS_AVAILABLE 0x3f
#define CARD_BACKUP_CAPS_READ 0x40
#define CARD_BACKUP_CAPS_WRITE 0x80
#define CARD_BACKUP_CAPS_PROGRAM 0x100
#define CARD_BACKUP_CAPS_VERIFY 0x200
#define CARD_BACKUP_CAPS_ERASE_PAGE 0x400
#define CARD_BACKUP_CAPS_ERASE_SECTOR 0x800
#define CARD_BACKUP_CAPS_ERASE_CHIP 0x1000
#define CARD_BACKUP_CAPS_READ_STATUS 0x2000
#define CARD_BACKUP_CAPS_WRITE_STATUS 0x4000
#define CARD_BACKUP_CAPS_ERASE_SUBSECTOR 0x8000
#define CARD_RESULT_UNSUPPORTED 3

void CARDi_IdentifyBackupCore2(int type)
{
    CARDiCommandArg *const command = cardi_common.command;

    MI_CpuFill8(&command->backup, 0, sizeof(command->backup));
    command->type = type;
    command->backup.capabilities =
        CARD_BACKUP_CAPS_AVAILABLE | CARD_BACKUP_CAPS_READ_STATUS;

    if (type != CARD_BACKUP_TYPE_NOT_USE) {
        const u32 size = 1 << ((type >> CARD_BACKUP_TYPE_SIZEBIT_SHIFT) &
                              CARD_BACKUP_TYPE_SIZEBIT_MASK);
        const int device = (type >> CARD_BACKUP_TYPE_DEVICE_SHIFT) &
                           CARD_BACKUP_TYPE_DEVICE_MASK;
        const int vendor = (type >> CARD_BACKUP_TYPE_VENDOR_SHIFT) &
                           CARD_BACKUP_TYPE_VENDOR_MASK;

        command->backup.totalSize = size;
        command->backup.initialStatus = 0xff;

        if (device == CARD_BACKUP_TYPE_DEVICE_EEPROM) {
            switch (size) {
            default:
                goto invalid_type;
            case 0x200:
                command->backup.pageSize = 0x10;
                command->backup.addressWidth = 1;
                command->backup.programPageTime = 5;
                command->backup.initialStatus = 0xf0;
                break;
            case 0x2000:
                command->backup.pageSize = 0x20;
                command->backup.addressWidth = 2;
                command->backup.programPageTime = 5;
                command->backup.initialStatus = 0;
                break;
            case 0x10000:
                command->backup.pageSize = 0x80;
                command->backup.addressWidth = 2;
                command->backup.programPageTime = 10;
                command->backup.initialStatus = 0;
                break;
            case 0x20000:
                command->backup.pageSize = 0x100;
                command->backup.addressWidth = 3;
                command->backup.programPageTime = 5;
                command->backup.initialStatus = 0;
                break;
            }

            command->backup.sectorSize = command->backup.pageSize;
            command->backup.capabilities |= CARD_BACKUP_CAPS_READ;
            command->backup.capabilities |= CARD_BACKUP_CAPS_PROGRAM;
            command->backup.capabilities |= CARD_BACKUP_CAPS_VERIFY;
            command->backup.capabilities |= CARD_BACKUP_CAPS_WRITE_STATUS;
        } else if (device == CARD_BACKUP_TYPE_DEVICE_FLASH) {
            switch (size) {
            default:
                goto invalid_type;
            case 0x40000:
            case 0x80000:
            case 0x100000:
                command->backup.writePageTime = 25;
                command->backup.writePageTotalTime = 300;
                command->backup.erasePageTime = 300;
                command->backup.eraseSectorTime = 5000;
                command->backup.capabilities |= CARD_BACKUP_CAPS_WRITE;
                command->backup.capabilities |= CARD_BACKUP_CAPS_ERASE_PAGE;
                break;
            case 0x200000:
                command->backup.writePageTime = 23;
                command->backup.writePageTotalTime = 300;
                command->backup.eraseSectorTime = 500;
                command->backup.eraseSectorTotalTime = 5000;
                command->backup.eraseChipTime = 10000;
                command->backup.eraseChipTotalTime = 60000;
                command->backup.initialStatus = 0;
                command->backup.capabilities |= CARD_BACKUP_CAPS_WRITE;
                command->backup.capabilities |= CARD_BACKUP_CAPS_ERASE_PAGE;
                command->backup.capabilities |= CARD_BACKUP_CAPS_ERASE_CHIP;
                command->backup.capabilities |= CARD_BACKUP_CAPS_WRITE_STATUS;
                break;
            case 0x400000:
                command->backup.eraseSectorTime = 600;
                command->backup.eraseSectorTotalTime = 3000;
                command->backup.eraseSubSectorTime = 70;
                command->backup.eraseSubSectorTotalTime = 150;
                command->backup.eraseChipTime = 23000;
                command->backup.eraseChipTotalTime = 800000;
                command->backup.initialStatus = 0;
                command->backup.subSectorSize = 0x1000;
                command->backup.capabilities |= CARD_BACKUP_CAPS_ERASE_SUBSECTOR;
                command->backup.capabilities |= CARD_BACKUP_CAPS_ERASE_CHIP;
                command->backup.capabilities |= CARD_BACKUP_CAPS_WRITE_STATUS;
                break;
            case 0x800000:
                if (vendor == 0) {
                    command->backup.eraseSectorTime = 1000;
                    command->backup.eraseSectorTotalTime = 3000;
                    command->backup.eraseChipTime = 68000;
                    command->backup.eraseChipTotalTime = 160000;
                    command->backup.initialStatus = 0;
                    command->backup.capabilities |= CARD_BACKUP_CAPS_ERASE_CHIP;
                    command->backup.capabilities |= CARD_BACKUP_CAPS_WRITE_STATUS;
                } else if (vendor == 1) {
                    command->backup.eraseSectorTime = 1000;
                    command->backup.eraseSectorTotalTime = 3000;
                    command->backup.eraseChipTime = 68000;
                    command->backup.eraseChipTotalTime = 160000;
                    command->backup.initialStatus = 0x84;
                    command->backup.capabilities |= CARD_BACKUP_CAPS_ERASE_CHIP;
                    command->backup.capabilities |= CARD_BACKUP_CAPS_WRITE_STATUS;
                }
                break;
            }

            command->backup.sectorSize = 0x10000;
            command->backup.pageSize = 0x100;
            command->backup.addressWidth = 3;
            command->backup.programPageTime = 5;
            command->backup.capabilities |= CARD_BACKUP_CAPS_READ;
            command->backup.capabilities |= CARD_BACKUP_CAPS_PROGRAM;
            command->backup.capabilities |= CARD_BACKUP_CAPS_VERIFY;
            command->backup.capabilities |= CARD_BACKUP_CAPS_ERASE_SECTOR;
        } else if (device == CARD_BACKUP_TYPE_DEVICE_FRAM) {
            switch (size) {
            default:
                goto invalid_type;
            case 0x2000:
            case 0x8000:
                break;
            }

            command->backup.pageSize = size;
            command->backup.sectorSize = size;
            command->backup.addressWidth = 2;
            command->backup.initialStatus = 0;
            command->backup.capabilities |= CARD_BACKUP_CAPS_READ;
            command->backup.capabilities |= CARD_BACKUP_CAPS_PROGRAM;
            command->backup.capabilities |= CARD_BACKUP_CAPS_VERIFY;
            command->backup.capabilities |= CARD_BACKUP_CAPS_WRITE_STATUS;
        } else {
        invalid_type:
            command->type = CARD_BACKUP_TYPE_NOT_USE;
            command->backup.totalSize = 0;
            cardi_common.command->result = CARD_RESULT_UNSUPPORTED;
            return;
        }
    }
}
