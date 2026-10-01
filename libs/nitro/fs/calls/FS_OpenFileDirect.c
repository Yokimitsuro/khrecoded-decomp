typedef struct FSFile {
    unsigned char reserved[8];
    void *archive;
    unsigned int status;
    void *commandArgument;
    int error;
} FSFile;

typedef struct FSOpenFileDirectArgument {
    unsigned int fileId;
    unsigned int imageTop;
    unsigned int imageBottom;
    unsigned int directoryIndex;
} FSOpenFileDirectArgument;

extern int FSi_SendCommand(FSFile *file, int command, int synchronous);

int FS_OpenFileDirect(
    FSFile *file,
    void *archive,
    unsigned int imageTop,
    unsigned int imageBottom,
    unsigned int fileId)
{
    FSOpenFileDirectArgument argument;

    file->archive = archive;
    file->commandArgument = &argument;
    argument.fileId = fileId;
    argument.imageTop = imageTop;
    argument.imageBottom = imageBottom;
    argument.directoryIndex = 0;
    return FSi_SendCommand(file, 7, 1);
}
