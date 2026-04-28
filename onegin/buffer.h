#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

struct StringsInfo {

    char *string_ptr;
    int string_size;
};

StringsInfo *MakePtrArray_AndSize(const char *file_name, int *text_size, char **buffer);

size_t GetFileSize(const char *file_name);
char *GetBuffer(const char *file_name, size_t *file_size);
int StringsCount(char *buffer);
struct StringsInfo *GetStruct_PtrStingsArray(char *buffer, size_t text_size);

#endif // BUFFER_H_INCLUDED
