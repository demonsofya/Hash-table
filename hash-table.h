#include "list/list.h"

#ifndef HASH_TABLE_H_INCLUDED
#define HASH_TABLE_H_INCLUDED

struct hash_table_t {
    list_t *table;
    int table_size;
};

hash_table_t CreateHashTable(int table_size);
int CheckIfStringIsInTableCellAndInsertIt(hash_table_t *hash_table, int cell_index, const char *compare_string);

int CountHash(const char *str);

int ZeroHash(const char *str);
int FirstLetterHash(const char *str);
int WorldLenHash(const char *str);
int AsciiSumHash(const char *str);

int DrawHashTableDump(hash_table_t *hash_table, const char *file_name, const char *function_name, int line_number);
int PrintHashCellsSizes(hash_table_t *hash_table);

#endif


