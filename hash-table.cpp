//#include "TXLib.h"
#include "list/list.h"
#include "hash-table.h"


#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

//-----------------------------------------------------------------------------

hash_table_t CreateHashTable(int table_size) {

    hash_table_t hash_table = {};

    hash_table.table = (list_t *) calloc(sizeof(list_t), table_size);
    hash_table.table_size = table_size; 

    return hash_table;
}

//-----------------------------------------------------------------------------

int CheckIfStringIsInTableCellAndInsertIt(hash_table_t *hash_table, int cell_index, const char *compare_string) {

    list_t curr_list = hash_table->table[cell_index];
    int curr_list_size = curr_list.list_size;

    if (curr_list_size == 0 || curr_list.data == NULL) {
        list_t new_list = ListCtor(2);
        InsertAfter(&new_list, 0, compare_string, 0);
        
        hash_table->table[cell_index] = new_list;
        return 0;
    }

    for (int i = GetHeadPosition(&curr_list); i > 0 && i < curr_list.elements_count; i = curr_list.next[i]) {
        char *curr_string = curr_list.data[i];
         
        if (curr_string == NULL)
            break;

        if (strcmp(compare_string, curr_string) == 0)
            return 1;
    }

    InsertAfter(&curr_list, 1, compare_string, 0);
    return 0;
}

//-----------------------------------------------------------------------------

int CountHash(const char *str) {
    return ZeroHash(str);
}

int ZeroHash(const char *str) {
    return 0;
}

int FirstLetterHash(const char *str) {
    return str[0];
}

int WorldLenHash(const char *str) {
    return strlen(str);
}

int AsciiSumHash(const char *str) {

    assert(str);
    
    int str_len = strlen(str);
    int sum = 0;

    for (int i =0; i < str_len; i++) 
        sum += str[i];

    return sum;
}




