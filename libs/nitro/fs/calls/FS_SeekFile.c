typedef struct FSFile {
    unsigned char reserved[0x10];
    void *commandArgument;
} FSFile;

typedef struct FSSeekFileArgument {
    int offset;
    int origin;
} FSSeekFileArgument;

extern int FSi_SendCommand(FSFile *file, int command, int synchronous);

int FS_SeekFile(FSFile *file, int offset, int origin)
{
    FSSeekFileArgument argument;

    file->commandArgument = &argument;
    argument.offset = offset;
    argument.origin = origin;
    return FSi_SendCommand(file, 14, 1);
}