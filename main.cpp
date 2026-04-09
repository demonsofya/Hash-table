//#include "TXLib.h"
#include "list/list.h"
#include "hash-table.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

const int MAX_WORD_LENGTH = 32;
const int HASH_TABLE_SIZE = 11;

const char *default_input_file_name = "preparing_text/pre_hamlet.txt";

int main(int argc, char *argv[]) {

    FILE *input_file = fopen(default_input_file_name, "r");
    if (input_file == NULL) {
        printf("Error with input file");
        return 0;
    }

    char curr_word[MAX_WORD_LENGTH] = "";
    hash_table_t hash_table = CreateHashTable(HASH_TABLE_SIZE); 

    int i = 0;

    while (feof(input_file) == 0 && i < 10) {
        fscanf(input_file, " %s", curr_word);
        int curr_hash = CountHash(curr_word);
//ON_DEBUG(fprintf(stderr, "curr word is '%s'", curr_word));

        CheckIfStringIsInTableCellAndInsertIt(&hash_table, curr_hash, curr_word);
        i++;
    }

    PrintHashCellsSizes(&hash_table);
    DrawHashTableDump(&hash_table, __FILE__, __FUNCTION__, __LINE__);
    return 0;
}