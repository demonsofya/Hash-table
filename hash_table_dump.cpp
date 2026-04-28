//#include "TXLib.h"
#include "list/list.h"
#include "hash-table.h"


#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

const int MAX_DUMP_MESSAGE_LEN                      = 100;
const int ONE_OUTPUT_FILE_COLUMN_SIZE               = 3;
const int SPACE_BETWEEN_COLUMNS_IN_OUTPUT_FILE_COUNT= 4;
const char *default_output_file_name = "HashTable_measures.txt";

extern const char *default_input_file_name;

int DrawHashTableDump(hash_table_t *hash_table, const char *file_name, const char *function_name, int line_number) {
    
    assert(hash_table);
    
    char message_string[MAX_DUMP_MESSAGE_LEN] = "";

    for (int i = 0; i < hash_table->table_size; i++) {
        snprintf(message_string, MAX_DUMP_MESSAGE_LEN, "DUMP FOR CEIL NUMBER %d", i);
        ListDump(&(hash_table->table[i]), file_name, function_name, line_number, message_string);
    }

    return 0;
}

int PrintHashCellsSizes(hash_table_t *hash_table) {

    assert(hash_table);
ON_DEBUG(fprintf(stderr, "starting print cells\n"));
    for (int i = 0; i < hash_table->table_size; i++) {
        fprintf(stderr, "%d %d\n", i, hash_table->table[i].elements_count);

        ON_DEBUG(
        if (hash_table->table[i].elements_count != 0) {
        for (int j = 1; j != 0; j = hash_table->table[i].next[j]) {
            fprintf(stderr, "[%s] ", hash_table->table[i].data[j]);
        } 
        fprintf(stderr, "\n");
        //for (int j = 0; j < hash_table->table[i].list_size; j++) {
        //    fprintf(stderr, "[%s] ", hash_table->table[i].data[j]);
        //} 
        //fprintf(stderr, "\n");
        }); 
    }

    return 0;
}

int PrintHashFuncs() {

    //const int hash_funcs_count = sizeof(HASH_FUNCS_ARRAY) / sizeof(hash_function_t);
    FILE *output_file = fopen(default_output_file_name, "w");

    hash_table_t hash_tables_array[HASH_FUNCS_COUNT] = {};
    for (int i = 0; i < HASH_FUNCS_COUNT; i++) {
        fprintf(output_file, "%d. %s;", i, HASH_FUNCS_ARRAY[i].hash_name);
        hash_tables_array[i] = CreateHashTableBasedOnDefaultFile(HASH_FUNCS_ARRAY[i]);
    }
    
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        fprintf(output_file, "\n");
        
        for (int j = 0; j < HASH_FUNCS_COUNT; j++)
            fprintf(output_file, "%d %d;", i, hash_tables_array[j].table[i].elements_count);  
    }

/*
    for (int i = 0; i < HASH_FUNCS_COUNT; i++) {
        hash_table_t hash_table = CreateHashTableBasedOnDefaultFile(HASH_FUNCS_ARRAY[i]);
        int curr_skipping_positions_count = 
            sizeof(char) * (ONE_OUTPUT_FILE_COLUMN_SIZE + SPACE_BETWEEN_COLUMNS_IN_OUTPUT_FILE_COUNT) * i;

        fseek(output_file, 0, SEEK_SET);
        for (int j = 0; j < hash_table.table_size; j++) {
            fseek(output_file, curr_skipping_positions_count, SEEK_CUR);
            
            fprintf(output_file, "%d %d\n", j, hash_table.table[j].elements_count);
        }

        HashTableDtor(&hash_table);
        fseek(output_file, 0, SEEK_SET);
    }
*/
    fclose(output_file);
    return 0;
}

hash_table_t CreateHashTableBasedOnDefaultFile(const hash_function_t curr_hash_func) {
    
    hash_table_t hash_table = CreateHashTable(HASH_TABLE_SIZE); 
    
    FILE *input_file = fopen(default_input_file_name, "r");
    assert(input_file);

    char curr_word[MAX_WORD_LENGTH] = "";
    while (feof(input_file) == 0) {
        fscanf(input_file, " %s", curr_word);
        int curr_hash = curr_hash_func.func(curr_word) % HASH_TABLE_SIZE;

        assert(curr_word);

        CheckIfStringIsInTableCellAndInsertIt(&hash_table, curr_hash, curr_word);
    }

    fclose(input_file);
    return hash_table;
}
