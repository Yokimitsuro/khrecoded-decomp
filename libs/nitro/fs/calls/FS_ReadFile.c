typedef struct FSFile {
    unsigned char reserved[16];
    void *commandArgument;
    int error;
} FSFile;

typedef struct FSReadFileArgument {
    void *destination;
    int length;
} FSReadFileArgument;

extern int FSi_SendCommand(FSFile *file, int command, int synchronous);

int FS_ReadFile(FSFile *file, void *destination, int length)
{
    FSReadFileArgument argument;

    file->commandArgument = &argument;
    argument.destination = destination;
    argument.length = length;
    if (FSi_SendCommand(file, 0, 1) != 0) {
        length = argument.length;
    } else {
        length = -1;
        if (file->error != 6) {
            length = argument.length;
        }
    }
    return length;
}
