#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <string.h>

#include "buffer.h"
#include "../hash-table.h"
//#include "output.h"

size_t GetFileSize(const char *file_name) {

    assert(file_name);

    struct stat file_info = {};
    stat(file_name, &file_info);

    return file_info.st_size;
}

StringsInfo *MakePtrArray_AndSize(const char *file_name, int *text_size, char **buffer) {

    assert(file_name);

    size_t file_size = 0;

    *buffer = GetBuffer(file_name, &file_size);
    *text_size = StringsCount(*buffer);
    return GetStruct_PtrStingsArray(*buffer, *text_size);

}

int StringsCount(char *buffer) {

    assert(buffer);

    int counter = 0;
    int curr_element = 0;

    while (buffer[curr_element] != '\0') {

        if (buffer[curr_element] == '\n')
            counter++;

        curr_element++;
    }

    return counter;
}

char *GetBuffer(const char *file_name, size_t *file_size) {

    assert(file_name);
    assert(file_size);

    size_t file_full_size = GetFileSize(file_name);
    char *buffer = (char *) calloc((file_full_size + 1), sizeof(char));
    buffer[file_full_size] = '\0';

    FILE *file_ptr = fopen(file_name, "r");

    *file_size = fread(buffer, sizeof(char), file_full_size, file_ptr);

    if (buffer[*file_size - 1] != '\n')
        buffer[*file_size] = '\n';

    buffer[*file_size + 1] = '\0';

    fclose(file_ptr);

    return buffer;
}

struct StringsInfo *GetStruct_PtrStingsArray(char *buffer, size_t text_size) {

    assert(buffer);

    StringsInfo* text = (StringsInfo *) calloc(text_size, sizeof(StringsInfo));

    assert(text);

    char *curr_pointer = buffer;

    for (size_t curr_num = 0; curr_num < text_size; curr_num++) {


        char *curr_string = curr_pointer;
        //text[curr_num].string_ptr = curr_pointer;

        curr_pointer = strchr(curr_pointer, '\n');
        *curr_pointer = '\0';
        curr_pointer++;

        text[curr_num].string_ptr = MyStrDup(curr_string);
        text[curr_num].string_size = curr_pointer - text[curr_num].string_ptr - 1; // \n не считаю

//PrintStringInFile(debug_ptr, text[curr_num].string_ptr);

//printf("\n\nstring number %d is %s, size is %d\n", curr_num + 1, text[curr_num].string_ptr, text[curr_num].string_size   );
   }

    return text;
}

