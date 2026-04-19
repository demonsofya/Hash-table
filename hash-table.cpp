//#include "TXLib.h"
#include "list/list.h"
#include "hash-table.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <nmmintrin.h>
#include <ammintrin.h>

//-----------------------------------------------------------------------------

hash_table_t CreateHashTable(int table_size) {

    hash_table_t hash_table = {};

    hash_table.table = (list_t *) calloc(sizeof(list_t), table_size);
    hash_table.table_size = table_size; 

    return hash_table;
}

void HashTableDtor(hash_table_t *hash_table) {

    if (hash_table == NULL)
        return;

    for (int i = 0; i < hash_table->table_size; i++) {
        ListDtor(&(hash_table->table[i]));
    }

    free(hash_table->table);
}

//-----------------------------------------------------------------------------

int CheckIfStringIsInTableCellAndInsertIt(hash_table_t *hash_table, int cell_index, const char *compare_string) {

    assert(hash_table);
    assert(compare_string);

    list_t *curr_list = &(hash_table->table[cell_index]);
    int curr_list_size = curr_list->list_size;

    if (curr_list_size == 0 || curr_list->data == NULL) {
        list_t new_list = ListCtor(2);
        InsertAfter(&new_list, 0, compare_string, 0);
        
        hash_table->table[cell_index] = new_list;
        return 0;
    }

    int search_result = CheckIfStringIsInTableCell_optimized(hash_table, cell_index, compare_string);
    if (search_result == 0)
        InsertAfter(curr_list, 1, compare_string, 0);
    
    return search_result;
}

int CheckIfStringIsInTableCell(hash_table_t *hash_table, int cell_index, const char *compare_string) {

    assert(hash_table);
    assert(compare_string);

    list_t *curr_list = &(hash_table->table[cell_index]);
    int curr_list_size = curr_list->list_size;

    if (curr_list_size == 0 || curr_list->data == NULL)
        return 0;

    for (int i = 1; i != 0; i = curr_list->next[i]) {
        char *curr_string = curr_list->data[i];
         
        if (curr_string == NULL)
            break;

        if (strcmp(compare_string, curr_string) == 0)
            return 1;
    }

    return 0;
}

int CheckIfStringIsInTableCell_optimized(hash_table_t *hash_table, int cell_index, const char *compare_string) {

    //list_t *curr_list = &(hash_table->table[cell_index]);

    if (hash_table->table[cell_index].list_size == 0)
        return 0;

    //asm volatile("vmovups ymm0, ymmword ptr [%0]\n" :: "r"(compare_string));
    for (int i = 1; i != 0; i = hash_table->table[cell_index].next[i]) {
        //char *curr_string = curr_list->data[i];
         
        //if (curr_string == NULL)
        //    break;
        
        bool cmp_result = 0;
        asm volatile(
            "vmovups ymm0, ymmword ptr [%1]\n"
            "vmovups ymm1, ymmword ptr [%2]\n"
            "vptest ymm0, ymm1\n"
            "setc %0\n"
            "vzeroupper" : "=r"(cmp_result) : "r"(compare_string), "r"(hash_table->table[cell_index].data[i]));
        if (cmp_result)
            return 1;
    }

    return 0;
}

int CheckIfStringIsInHashTable(hash_table_t *hash_table, const char *compare_string) {
    
    assert(hash_table);
    assert(compare_string);

    int cell_index = CountHash(compare_string);
    return CheckIfStringIsInTableCell(hash_table, cell_index, compare_string);
}

//-----------------------------------------------------------------------------

int CountHash(const char *str) {
    return Crc32Hash_optimized(str) % HASH_TABLE_SIZE;
}

int ZeroHash(const char *str) {
    return 0;
}

int FirstLetterHash(const char *str) {
    
    assert(str);

    return str[0];
}

int WorldLenHash(const char *str) {
    
    assert(str);

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

unsigned long long RolFunc(unsigned long long number) { // Машинный код превращает это в rol
    int shift = (sizeof(unsigned long long) << 3) - 1;
    return (number << 1) | (number >> shift);
}

unsigned long long RorFunc(unsigned long long number) { // Машинный код превращает это в ror
    int shift = (sizeof(unsigned long long) << 3) - 1;
    return (number >> 1) | (number << shift);
}

unsigned long long RolHash(const char *str) {

    assert(str);

    unsigned long long hash = str[0];
    int str_len = strlen(str);
    for (int i = 1; i < str_len; i++)
        hash = RolFunc(hash) ^ str[i]; 

    return hash;
}

unsigned long long RorHash(const char *str) {

    assert(str);

    unsigned long long hash = str[0];
    int str_len = strlen(str);
    
    for (int i = 1; i < str_len; i++)
        hash = RorFunc(hash) ^ str[i]; 

    return hash;
}

unsigned long DJB2Hash(const char *str) {

    assert(str);

    unsigned long hash = 5381;
    int str_len = strlen(str);

    for (int i = 1; i < str_len; i++)
        hash = ((hash << 5) + hash) + str[i]; /* hash * 33 + c */

    return hash;
}

const int POLY = 0x11EDC6F41;

unsigned int Crc32Hash_optimized(const char *str) {

    // assert'a не будет

    unsigned int start_hash = -1;
    int str_len = strlen(str);

    for (int i = 0; i < str_len; i++)
        start_hash = _mm_crc32_u8(start_hash, str[i]);

    return start_hash;  
}

unsigned int CRC32Hash(const char *str) {
    
    assert(str);

    unsigned int hash = -1;

    int str_len = strlen(str);
 
    for (int i = 0; i < str_len; i++) {
        hash = hash ^ str[i];
        
        for (int bit = 0; bit < 8; bit++) {
            if (hash & 1) 
                hash = (hash >> 1) ^ POLY;
            else          
                hash = (hash >> 1);
        }
    }
   
    return ~hash;
}



char *MyStrDup(const char *str) {

    assert(str);
    
    char *new_str = (char *) calloc(MAX_WORD_LENGTH, sizeof(char));
    int insert_str_len = strlen(str), i = 0;
    
    for (; i < insert_str_len; i++)
        new_str[i] = str[i];
    for (; i < MAX_WORD_LENGTH; i++) 
        new_str[i] = '\0';

    return new_str;
}

