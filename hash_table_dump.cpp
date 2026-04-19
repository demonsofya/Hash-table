//#include "TXLib.h"
#include "list/list.h"
#include "hash-table.h"


#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

const int MAX_DUMP_MESSAGE_LEN = 100;

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
