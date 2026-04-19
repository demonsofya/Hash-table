#include <stdio.h>
#include <assert.h>

const int TXT_PREP_MAX_FILE_NAME_LENGTH = 64;
const int MAX_WORD_LENGTH = 32;

const char file_name[] = "othello.txt";
const char prepared_file_name[] = "pre_othello.txt";

int main() {
    FILE *input_file = fopen (file_name, "r");

    if (input_file == NULL) {
        printf("Input file error\n");
        return 0;
    }

    FILE *output_file = fopen(prepared_file_name, "w");
    assert (output_file);

    char word[MAX_WORD_LENGTH] = {};

    for (; !feof (input_file);) {

        int fscanf_status = fscanf(input_file, " %[^-;,.\"*:?\n\r!() ]", word); 

        if (fscanf_status != EOF && fscanf_status != 0)
            fprintf (output_file, "%s\n", word); 

        if (fscanf_status != EOF)
            fgetc (input_file);
    }

    fclose (input_file);
    fclose (output_file);

    return 0;
}
