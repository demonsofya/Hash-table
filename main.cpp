//#include "TXLib.h"
#include "list/list.h"
#include "hash-table.h"
#include "onegin/buffer.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <intrin.h>

const char *default_input_file_name     = "preparing_text/pre_hamlet.txt";
const char *default_search_file_name    = "preparing_text/pre_othello.txt";

int main(int argc, char *argv[]) {

    //printf("len of %s is %d\n", "aboba", MyStrlen("aboba"));
    //return 0;

    FILE *input_file = fopen(default_input_file_name, "r");
    if (input_file == NULL) {
        printf("Error with input file");
        return 0;
    }

    char curr_word[MAX_WORD_LENGTH] = "";
    hash_table_t hash_table = CreateHashTable(HASH_TABLE_SIZE); 

    while (feof(input_file) == 0) {
        fscanf(input_file, " %s", curr_word);
        int curr_hash = CountHash(curr_word);

        assert(curr_word);
//ON_DEBUG(fprintf(stderr, "curr word is '%s'", curr_word));

        CheckIfStringIsInTableCellAndInsertIt(&hash_table, curr_hash, curr_word);
    }
    //PrintHashFuncs();
    //PrintHashCellsSizes(&hash_table);

    size_t file_size = 0;
    char *buffer_start = NULL;
    int strings_count = 0;
    StringsInfo *strings_array = MakePtrArray_AndSize(default_search_file_name, &strings_count, &buffer_start);

    int curr_word_len = 0, search_result = 0;

    for (int j = 0; j < 10; j++) {
        unsigned long long start_ticks = __rdtsc();
        
        for (int i = 0; i < 300; i++) { //тут я въебала цикл фор чтобы у меня поиск перебил все остальные вызываемые функции            
            for (int k = 0; k < strings_count; k++) {
                
                search_result = CheckIfStringIsInHashTable(&hash_table, strings_array[k].string_ptr);
ON_DEBUG(printf("%s %d\n", strings_array[k].string_ptr, search_result));
            }
            
            /*
            while (buffer != NULL && *buffer != '\0') {
                sscanf(buffer, " %s%n", curr_word, &curr_word_len);
                buffer += curr_word_len;

                //assert(curr_word);
                for (int i = curr_word_len; i < MAX_WORD_LENGTH; i++) 
                    curr_word[i] = '\0';

                search_result = CheckIfStringIsInHashTable(&hash_table, curr_word);
            }
            */

        }
        unsigned long long end_ticks = __rdtsc();
        printf("Ticks count: %llu\n", end_ticks - start_ticks);
    }

    HashTableDtor(&hash_table);
    return 0;
}