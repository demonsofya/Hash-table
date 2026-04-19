#include "list/list.h"

#ifndef HASH_TABLE_H_INCLUDED
#define HASH_TABLE_H_INCLUDED

const int MAX_WORD_LENGTH = 32;
const int HASH_TABLE_SIZE = 4001;

struct hash_table_t {
    list_t *table;
    int table_size;
};

hash_table_t CreateHashTable(int table_size);
int CheckIfStringIsInTableCellAndInsertIt(hash_table_t *hash_table, int cell_index, const char *compare_string);
int CheckIfStringIsInTableCell(hash_table_t *hash_table, int cell_index, const char *compare_string);
int CheckIfStringIsInHashTable(hash_table_t *hash_table, const char *compare_string);
int CheckIfStringIsInTableCell_optimized(hash_table_t *hash_table, int cell_index, const char *compare_string);

int CountHash(const char *str);

int ZeroHash(const char *str);
int FirstLetterHash(const char *str);
int WorldLenHash(const char *str);
int AsciiSumHash(const char *str);
unsigned long long RolHash(const char *str);
unsigned long long RorHash(const char *str);
unsigned long DJB2Hash(const char *str);
unsigned int CRC32Hash(const char *str);
unsigned int Crc32Hash_optimized(const char *str);

int DrawHashTableDump(hash_table_t *hash_table, const char *file_name, const char *function_name, int line_number);
int PrintHashCellsSizes(hash_table_t *hash_table);

void HashTableDtor(hash_table_t *hash_table);

unsigned long long RolFunc(unsigned long long number); // Машинный код превращает это в rol
unsigned long long RorFunc(unsigned long long number); // Машинный код превращает это в ror

char *MyStrDup(const char *str);

#endif


